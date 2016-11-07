namespace render {

PlyLoader::PlyLoader(Device *device) : device(device) {
}

Ref<Mesh> PlyLoader::load(const char *filename) {
    max_index = 0;
    last_face_count = 0;
    for (uint prop = 0; prop < MAX_PROPS; ++prop) {
        prop_counts[prop] = 0;
    }
    
    long nvertices, ntriangles;
    p_ply ply = ply_open(filename, NULL, 0, NULL);
    if (!ply) {
        fatal_error("error opening ply file");
    }
    if (!ply_read_header(ply)) {
        fatal_error("error reading ply header");
    }

    nvertices = ply_set_read_cb(ply, "vertex", "x", vertex_cb, this, PROP_X);
    ply_set_read_cb(ply, "vertex", "y", vertex_cb, this, PROP_Y);
    ply_set_read_cb(ply, "vertex", "z", vertex_cb, this, PROP_Z);
    ply_set_read_cb(ply, "vertex", "nx", vertex_cb, this, PROP_NX);
    ply_set_read_cb(ply, "vertex", "ny", vertex_cb, this, PROP_NY);
    ply_set_read_cb(ply, "vertex", "nz", vertex_cb, this, PROP_NZ);
    
    ntriangles = ply_set_read_cb(ply, "face", "vertex_indices", face_cb, this, 0);

    verts.reserve(nvertices * 3);
    indexes.reserve(ntriangles * 3);
    
    if (!ply_read(ply)) {
        fatal_error("error reading ply file");
    }
    ply_close(ply);

    if (max_index >= verts.size()) {
        fatal_error("overflowing vertex index: %d", (int)max_index);
    }
    
    MeshMode mode;
    switch (last_face_count) {
    case 1: mode = MESH_POINTS; break;
    case 2: mode = MESH_LINES; break;
    case 3: mode = MESH_TRIANGLES; break;
    default:
        fatal_error("unsupported face count: %d", (int)last_face_count);
    }

    uint vert_element_count = 0;
    uint last_count = 0;
    for (uint prop = 0; prop < MAX_PROPS; ++prop) {
        uint count = prop_counts[prop];
        if (count) {
            if (last_count) {
                if (last_count != count) {
                    fatal_error("inconsistent vertex element count");
                }
            } else {
                last_count = count;
            }
            ++vert_element_count;
        }
    }

    Ref<VertexFormat> format(device->create_vertex_format());
    if (prop_counts[PROP_X]) {
        format->add(0, VertexFormat::POSITION, VALUE_TYPE_FLOAT, 3);
    }
    if (prop_counts[PROP_NX]) {
        format->add(1, VertexFormat::NORMAL, VALUE_TYPE_FLOAT, 3);
    }

    Ref<Mesh> mesh(device->create_mesh(mode, 1));    

    Ref<BufferObject> vertex_buffer(device->create_buffer_object());
    vertex_buffer->bind(BUFFER_TARGET_WRITE);
    vertex_buffer->data(sizeof(verts[0]) * verts.size(), &verts[0]);
    vertex_buffer->unbind();
    mesh->set_vertex_buffer(0, vertex_buffer.ptr(), format.ptr());

    if (indexes.size() > 0) {
        Ref<BufferObject> index_buffer(device->create_buffer_object());
        index_buffer->bind(BUFFER_TARGET_WRITE);
        ValueType index_type = VALUE_TYPE_UINT;
        
        if (max_index <= 0xffff) {
            PODVector<ushort> small_indexes(indexes.size());
            for (uint i = 0; i < indexes.size(); ++i) {
                small_indexes[i] = (ushort)indexes[i];
            }
            index_buffer->data(sizeof(small_indexes[0]) * small_indexes.size(), &small_indexes[0]);
            index_type = VALUE_TYPE_USHORT;
        } else {
            index_buffer->data(sizeof(indexes[0]) * indexes.size(), &indexes[0]);
        }
        
        index_buffer->unbind();
        mesh->set_index_buffer(index_buffer.ptr(), indexes.size(), index_type);
    } else {
        mesh->set_num_vertexes(verts.size() / vert_element_count);
    }
    
    return mesh;
}

int PlyLoader::vertex_cb(p_ply_argument argument) {
    float value = (float)ply_get_argument_value(argument);

    PlyLoader *loader;
    long prop;
    ply_get_argument_user_data(argument, (void **)&loader, &prop);

    ++loader->prop_counts[prop];
    loader->verts.push_back(value);
    return 1;
}

int PlyLoader::face_cb(p_ply_argument argument) {
    long count, index;
    ply_get_argument_property(argument, NULL, &count, &index);
    if (index < 0) {
        return 1;
    }

    PlyLoader *loader;
    ply_get_argument_user_data(argument, (void **)&loader, NULL);
    
    if (loader->last_face_count) {
        if (loader->last_face_count != count) {
            fatal_error("all faces required to have equal vertex count");
        }
    } else {
        loader->last_face_count = count;
    }
    
    uint value = (uint)ply_get_argument_value(argument);
    if (value > loader->max_index) {
        loader->max_index = value;
    }
    
    loader->indexes.push_back(value);
    return 1;
}

}


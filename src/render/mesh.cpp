namespace render {

Mesh::Mesh(MeshMode mode, uint num_vertex_buffers) {
    _mode = mode;
    glGenVertexArrays(1, &_vao);

    _index_buffer = 0;
    _num_indexes = 0;
    _index_type = VALUE_TYPE_USHORT;

    _num_vertexes = 0;

    _num_buffers = num_vertex_buffers;
    _buffers = new Ref<BufferObject>[num_vertex_buffers];
    _formats = new Ref<VertexFormat>[num_vertex_buffers];

    _dirty = true;
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &_vao);
    delete[] _buffers;
    delete[] _formats;
}

MeshMode Mesh::mode() {
    return _mode;
}

uint Mesh::num_vertexes() {
    return _num_vertexes;
}

void Mesh::set_num_vertexes(uint num) {
    _index_buffer = NULL;
    _num_indexes = 0;
    _num_vertexes = num;
    _dirty = true;
}

BufferObject *Mesh::index_buffer() {
    return _index_buffer.ptr();
}

uint Mesh::num_indexes() {
    return _num_indexes;
}

ValueType Mesh::index_type() {
    return _index_type;
}

void Mesh::set_index_buffer(BufferObject *buf, uint num_indexes, ValueType type) {
    assert(value_type_is_integer(type));
    _index_buffer = buf;
    _num_indexes = num_indexes;
    _index_type = type;
    _num_vertexes = 0;
    _dirty = true;
}

uint Mesh::num_vertex_buffers() {
    return _num_buffers;
}

BufferObject *Mesh::vertex_buffer(uint i) {
    assert(i < _num_buffers);
    return _buffers[i].ptr();
}

VertexFormat *Mesh::vertex_format(uint i) {
    assert(i < _num_buffers);
    return _formats[i].ptr();
}

void Mesh::set_vertex_buffer(uint i, BufferObject *buf, VertexFormat *format) {
    _buffers[i] = buf;
    _formats[i] = format;
    _dirty = true;
}

void Mesh::bind() {
    glBindVertexArray(_vao);

    if (!_dirty)
        return;
    _dirty = false;

    for (uint i = 0; i < _num_buffers; ++i) {
        VertexFormat *fmt = _formats[i].ptr();
        BufferObject *buf = _buffers[i].ptr();
        if (!fmt)
            continue;
        if (!buf)
            continue;

        buf->bind(BUFFER_TARGET_VERTEX);

        for (uint i = 0; i < fmt->attrib_count(); ++i) {
            const VertexFormat::Attrib &attrib = fmt->attrib(i);
            glEnableVertexAttribArray(attrib.index);
            uint stride = fmt->stride();
            if (!value_type_is_integer(attrib.spec.type)) {
                glVertexAttribPointer(attrib.index, attrib.spec.count, from_value_type(attrib.spec.type),
                                      attrib.spec.normalized, stride, (const GLvoid *)(ptrdiff_t)attrib.offset);
            } else {
                assert(!attrib.spec.normalized);
                glVertexAttribIPointer(attrib.index, attrib.spec.count, from_value_type(attrib.spec.type),
                                       stride, (const GLvoid *)(ptrdiff_t)attrib.offset);
            }
        }
    }

    if (_index_buffer)
        _index_buffer->bind(BUFFER_TARGET_INDEX);
}

void Mesh::unbind() {
    glBindVertexArray(0);
}

void Mesh::draw(uint offset, uint count) {
    if (_index_buffer) {
        if (!count)
            count = _num_indexes;
        assert(offset + count <= _num_indexes);
        uint prim_size = value_type_byte_size(_index_type);
        glDrawElements(from_mesh_mode(_mode), count, from_value_type(_index_type),
                       reinterpret_cast<void *>(offset * prim_size));
    } else {
        if (!count)
            count = _num_vertexes;
        assert(offset + count <= _num_vertexes);
        glDrawArrays(from_mesh_mode(_mode), offset, count);
    }
}

}


typedef struct t_ply_argument_ *p_ply_argument;

namespace render {

class PlyLoader {
public:
    PlyLoader(Device *device);
    
    Ref<Mesh> load(const char *filename);

private:
    enum {
        PROP_X,
        PROP_Y,
        PROP_Z,
        PROP_NX,
        PROP_NY,
        PROP_NZ,
        MAX_PROPS
    };
    
    static int vertex_cb(p_ply_argument argument);
    static int face_cb(p_ply_argument argument);

    Device *device;
    PODVector<float> verts;
    PODVector<uint> indexes;

    uint max_index;
    long last_face_count;
    uint prop_counts[MAX_PROPS];
};

}


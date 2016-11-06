namespace render {

class Mesh : public RefCounted {
public:
    MeshMode mode();

    // either use this
    uint num_vertexes();
    void set_num_vertexes(uint num);

    // or an index buffer
    BufferObject *index_buffer();
    uint num_indexes();
    ValueType index_type();
    void set_index_buffer(BufferObject *buf, uint num_indexes, ValueType type = VALUE_TYPE_SHORT);

    uint num_vertex_buffers();
    BufferObject *vertex_buffer(uint i);
    VertexFormat *vertex_format(uint i);
    void set_vertex_buffer(uint i, BufferObject *buf, VertexFormat *format);

    void bind();
    void unbind();

    void draw(uint offset = 0, uint count = 0);

private:
    Mesh(MeshMode mode, uint num_vertex_buffers);
    ~Mesh();
    
    Mesh(const Mesh &);
    Mesh &operator=(const Mesh &);

    friend class Device;
    
    MeshMode _mode;
    uint _vao;

    Ref<BufferObject> _index_buffer;
    uint _num_indexes;
    ValueType _index_type;

    uint _num_vertexes;

    uint _num_buffers;
    Ref<BufferObject> *_buffers;
    Ref<VertexFormat> *_formats;

    bool _dirty;
};

}


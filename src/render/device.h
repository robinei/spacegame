namespace render {

class Device : public RefCounted {
public:
    static Ref<Device> create(SDL_Window *window);

    Ref<Shader> create_shader(ShaderType type);
    Ref<Shader> compile_shader(ShaderType type, const char *text);
    Ref<Shader> load_shader(ShaderType type, const char *path);
    Ref<Program> create_program();
    Ref<BufferObject> create_buffer_object();
    Ref<VertexFormat> create_vertex_format(bool manual_layout = false);
    Ref<Mesh> create_mesh(MeshMode mode, uint num_vertex_buffers);
    Ref<Texture> create_texture();
    Ref<Texture> load_texture(const char *path);
    Ref<Texture> load_texture_cubemap(const char *paths[6]);

    void clear(); // temporary
    
private:
    Device(SDL_Window *window);
    ~Device();

    friend class BufferObject;
    friend class Program;

    void *gl_context;
    Program *bound_program;
    BufferObject *bound_buffers[8];
};

}


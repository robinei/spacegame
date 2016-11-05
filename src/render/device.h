
class Device : public RefCounted {
public:
    Device(SDL_Window *window);
    ~Device();

    Ref<BufferObject> create_buffer_object();
    Ref<Program> create_program();
    Ref<Shader> create_shader(ShaderType type);
    Ref<Shader> compile_shader(ShaderType type, const char *text);
    Ref<Shader> load_shader(ShaderType type, const char *path);

    void clear(); // temporary
    
private:
    friend class BufferObject;
    friend class Program;

    void *gl_context;
    
    enum { GENERAL_TARGET_COUNT = 2 };
    enum { TARGET_COUNT = 8 };
    BufferObject *target_buffers[TARGET_COUNT];

    Program *bound_program;

    void ensure_bound_to_general_target(BufferObject *buffer);
    void ensure_bound_to_general_targets(BufferObject *buffer0, BufferObject *buffer1);
    void unbind(BufferObject *buffer);

    void maybe_bind(Program *program);
    void maybe_unbind(Program *program);
};


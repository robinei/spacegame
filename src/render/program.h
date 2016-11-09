namespace render {

class Program : public RefCounted {
public:
    void bind();
    void unbind();

    void set_vertex_format(Ref<VertexFormat> format);
    VertexFormat *vertex_format();

    void attach(Ref<Shader> shader);
    void detach(Shader *shader);
    void detach_all();
    
    void link();

    int attrib_location(const char *name);
    void attrib(const char *name, uint index);

    int uniform_location(const char *name);
    void uniform(int location, float value);
    void uniform(int location, int value);
    void uniform(int location, const Vec2 &value);
    void uniform(int location, const Vec3 &value);
    void uniform(int location, const Vec4 &value);
    void uniform(int location, const Mat4 &value);

    template <typename T>
    void uniform(const char *name, T value) {
        uniform(uniform_location(name), value);
    }

private:
    Program(Device *device);
    ~Program();

    Program(const Program &);
    Program &operator=(const Program &);

    friend class Device;

    Device *_device;
    uint _program;
    Ref<VertexFormat> _vertex_format;
    Ref<Shader> _shaders[2];
};

}


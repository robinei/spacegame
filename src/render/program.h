
class Shader : public RefCounted {
public:
    void compile(const char *text);
    void load(const char *path);

    ShaderType type() { return _type; }

protected:
    Shader(ShaderType type);
    ~Shader();

private:
    friend class Device;
    friend class Program;
    
    ShaderType _type;
    unsigned int _shader;
};


class Program : public RefCounted {
public:
    void attach(Shader *shader);
    Shader *attached(ShaderType type);
    void detach(Shader *shader);
    void detach(ShaderType type);
    void detach_all();

    void link();
	
    void bind();
    void unbind();

    int attrib_location(const char *name);
    void attrib(const char *name, unsigned int index);

    int uniform_location(const char *name);
    void uniform(int location, float value);
    void uniform(int location, int value);
/*    void uniform(int location, const vec2 &value);
    void uniform(int location, const vec3 &value);
    void uniform(int location, const vec4 &value);
    void uniform(int location, const mat2 &value);
    void uniform(int location, const mat3 &value);
    void uniform(int location, const mat4 &value);*/

    template <typename T>
    void uniform(const char *name, T value) {
        uniform(uniform_location(name), value);
    }

protected:
    Program(Device *device);
    ~Program();

private:
    Program(const Program &);
    Program &operator=(const Program &);

    friend class Device;

    Device *_device;
    Ref<Shader> _shaders[2];
    unsigned int _program;
};


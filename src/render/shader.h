namespace render {

class Shader : public RefCounted {
public:
    void compile(const char *text);
    void load(const char *path);

    ShaderType type() { return _type; }

private:
    Shader(ShaderType type);
    ~Shader();

    Shader(const Shader &);
    Shader &operator=(const Shader &);

    friend class Device;
    friend class Program;
    
    ShaderType _type;
    uint _shader;
};

}


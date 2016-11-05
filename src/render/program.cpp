
enum { SHADER_TYPE_COUNT = 2 };


static char *load_file(const char *path) {
    FILE *fp = fopen(path, "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    unsigned int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *result = (char *)malloc(size + 1);
    fread(result, 1, size, fp);
    fclose(fp);
    result[size] = 0;
    return result;
}


Shader::Shader(ShaderType type) : _type(type) {
    assert((int)type < SHADER_TYPE_COUNT);
    _shader = glCreateShader(translateShaderType(type));
}

Shader::~Shader() {
    glDeleteShader(_shader);
}

void Shader::compile(const char *text) {
    GLint length = strlen(text);
    glShaderSource(_shader, 1, (const GLchar**)&text, &length);
    glCompileShader(_shader);

    GLint result;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);
        char *log = (char *)malloc(length + 1);
        glGetShaderInfoLog(_shader, length, &result, log);
        log[length] = 0;
        fatal_error("error compiling shader:\n\n%s", log);
    }
}

void Shader::load(const char *path) {
    char *data = load_file(path);
    compile(data);
    free(data);
}




Program::Program(Device *device) {
    _device = device;
    _program = glCreateProgram();
    assert(_program);
}

Program::~Program() {
    _device->maybe_unbind(this);
    glDeleteProgram(_program);
}

void Program::attach(Shader *shader) {
    glAttachShader(_program, shader->_shader);
    _shaders[shader->type()] = shader;
}

Shader *Program::attached(ShaderType type) {
    assert((int)type < SHADER_TYPE_COUNT);
    return _shaders[type].ptr();
}

void Program::detach(Shader *shader) {
    Ref<Shader> &slot = _shaders[shader->type()];
    assert(slot == shader);
    glDetachShader(_program, shader->_shader);
    slot = 0;
}

void Program::detach_all() {
    for (int i = 0; i < 6; ++i)
        if (_shaders[i])
            detach(_shaders[i].ptr());
}

void Program::detach(ShaderType type) {
    assert((int)type < SHADER_TYPE_COUNT);    
    detach(_shaders[type].ptr());
}

void Program::link() {
    glLinkProgram(_program);

    GLint result, length;
    glGetProgramiv(_program, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);
        char *log = (char *)malloc(length + 1);
        glGetProgramInfoLog(_program, length, &result, log);
        log[length] = 0;
        fatal_error("error linking program:\n\n%s", log);
    }
}

GLint Program::attrib_location(const char *name) {
    return glGetAttribLocation(_program, name);
}

void Program::attrib(const char *name, GLuint index) {
    glBindAttribLocation(_program, index, name);
}

GLint Program::uniform_location(const char *name) {
    return glGetUniformLocation(_program, name);
}

void Program::uniform(GLint location, GLfloat value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniform1f(location, value);
}

void Program::uniform(GLint location, GLint value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniform1i(location, value);
}

/*
void Program::uniform(GLint location, const vec2 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniform2fv(location, 1, glm::value_ptr(value));
}

void Program::uniform(GLint location, const vec3 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Program::uniform(GLint location, const vec4 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniform4fv(location, 1, glm::value_ptr(value));
}

void Program::uniform(GLint location, const mat2 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::uniform(GLint location, const mat3 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Program::uniform(GLint location, const mat4 &value) {
    _device->maybe_bind(this);
    assert(location >= 0);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
*/


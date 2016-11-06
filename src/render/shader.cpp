namespace render {

static char *load_file(const char *path) {
    FILE *fp = fopen(path, "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    uint size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *result = (char *)malloc(size + 1);
    fread(result, 1, size, fp);
    fclose(fp);
    result[size] = 0;
    return result;
}


Shader::Shader(ShaderType type) : _type(type) {
    _shader = glCreateShader(from_shader_type(type));
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

}


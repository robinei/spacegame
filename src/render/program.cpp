namespace render {

Program::Program(Device *device) {
    _device = device;
    _program = glCreateProgram();
    assert(_program);
}

Program::~Program() {
    unbind();
    glDeleteProgram(_program);
}

void Program::bind() {
    if (_device->bound_program == this) {
        return;
    }
    if (_device->bound_program) {
        _device->bound_program->unbind();
    }
    glUseProgram(_program);
    _device->bound_program = this;
}

void Program::unbind() {
    if (_device->bound_program == this) {
        glUseProgram(0);
        _device->bound_program = NULL;
    }
}

void Program::set_vertex_format(Ref<VertexFormat> format) {
    _vertex_format = format;
}

VertexFormat *Program::vertex_format() {
    return _vertex_format.ptr();
}

void Program::attach(Ref<Shader> shader) {
    Ref<Shader> &old(_shaders[shader->type()]);
    if (old == shader) {
        return;
    }
    if (old) {
        detach(old.ptr());
    }
    _shaders[shader->type()] = shader;
    glAttachShader(_program, shader->_shader);
}

void Program::detach(Shader *shader) {
    Ref<Shader> &slot = _shaders[shader->type()];
    assert(slot == shader);
    glDetachShader(_program, shader->_shader);
    slot = 0;
}

void Program::detach_all() {
    for (uint i = 0; i < 2; ++i) {
        if (_shaders[i]) {
            detach(_shaders[i].ptr());
        }
    }
}

void Program::link() {
    assert(_vertex_format);

    for (uint i = 0; i < _vertex_format->attrib_count(); ++i) {
        const VertexFormat::Attrib &a(_vertex_format->attrib(i));
        attrib(a.spec.name, a.index);
    }

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

int Program::attrib_location(const char *name) {
    return glGetAttribLocation(_program, name);
}

void Program::attrib(const char *name, uint index) {
    glBindAttribLocation(_program, index, name);
}

int Program::uniform_location(const char *name) {
    return glGetUniformLocation(_program, name);
}

void Program::uniform(int location, float value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniform1f(location, value);
}

void Program::uniform(int location, int value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniform1i(location, value);
}

void Program::uniform(int location, const Vec2 &value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniform2fv(location, 1, &value[0]);
}

void Program::uniform(int location, const Vec3 &value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniform3fv(location, 1, &value[0]);
}

void Program::uniform(int location, const Vec4 &value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniform4fv(location, 1, &value[0]);
}

void Program::uniform(int location, const Mat4 &value) {
    assert(_device->bound_program == this);
    assert(location >= 0);
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0]);
}

}


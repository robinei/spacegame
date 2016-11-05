
Device::Device(SDL_Window *window) {
    for (int i = 0; i < TARGET_COUNT; ++i) {
        target_buffers[i] = 0;
    }
    bound_program = 0;

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context)
        fatal_error("SDL_GL_CreateContext() error: %s", SDL_GetError());

    glewExperimental = GL_TRUE;
    GLenum status = glewInit();
    if (status != GLEW_OK)
        fatal_error("glewInit() error: %s", glewGetErrorString(status));

    if (!GLEW_VERSION_3_1)
        fatal_error("OpenGL 3.1 API is not available.");

    if (SDL_GL_SetSwapInterval(-1) < 0) {
        printf("SDL_GL_SetSwapInterval(-1) failed: %s\n", SDL_GetError());
        if (SDL_GL_SetSwapInterval(1) < 0)
            printf("SDL_GL_SetSwapInterval(1) failed: %s\n", SDL_GetError());
    }
}

Device::~Device() {
    SDL_GL_DeleteContext((SDL_GLContext)gl_context);
}

Ref<BufferObject> Device::create_buffer_object() {
    return Ref<BufferObject>(new BufferObject(this));
}

Ref<Program> Device::create_program() {
    return Ref<Program>(new Program(this));
}

Ref<Shader> Device::create_shader(ShaderType type) {
    return Ref<Shader>(new Shader(type));
}

Ref<Shader> Device::compile_shader(ShaderType type, const char *text) {
    Ref<Shader> shader = create_shader(type);
    shader->compile(text);
    return shader;
}

Ref<Shader> Device::load_shader(ShaderType type, const char *path) {
    Ref<Shader> shader = create_shader(type);
    shader->load(path);
    return shader;
}

void Device::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}


void Device::ensure_bound_to_general_target(BufferObject *buffer) {
    assert(!buffer->_pinned_to_target);
    const int base = BUFFER_TARGET_GENERAL0;
    for (int i = 0; i < GENERAL_TARGET_COUNT; ++i) {
        if (target_buffers[base + i] == buffer) {
            return;
        }
    }
    for (int i = 0; i < GENERAL_TARGET_COUNT; ++i) {
        BufferObject *candidate = target_buffers[base + i];
        if (!candidate->_pinned_to_target) {
            unbind(candidate);
            buffer->_target = (BufferTarget)(base + i);
            target_buffers[buffer->_target] = buffer;
            glBindBuffer(translateBufferTarget(buffer->_target), buffer->_handle);
            return;
        }
    }
    fatal_error("not enough available general buffer targets");
}

void Device::ensure_bound_to_general_targets(BufferObject *buffer0, BufferObject *buffer1) {
    ensure_bound_to_general_target(buffer0);
    buffer0->_pinned_to_target = true;
    ensure_bound_to_general_target(buffer1);
    buffer0->_pinned_to_target = false;
}

void Device::unbind(BufferObject *buffer) {
    assert(!buffer->_pinned_to_target);
    if (buffer->_target) {
        assert(buffer == target_buffers[buffer->_target]);
        glBindBuffer(translateBufferTarget(buffer->_target), 0);
        target_buffers[buffer->_target] = 0;
        buffer->_target = BUFFER_TARGET_INVALID;
    }
}

void Device::maybe_bind(Program *program) {
    if (bound_program == program) {
        return;
    }
    if (bound_program) {
        maybe_unbind(bound_program);
    }
    glUseProgram(program->_program);
    bound_program = program;
}

void Device::maybe_unbind(Program *program) {
    if (bound_program == program) {
        glUseProgram(0);
        bound_program = 0;
    }
}


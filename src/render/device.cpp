namespace render {

Ref<Device> Device::create(SDL_Window *window) {
    return ref(new Device(window));
}

Device::Device(SDL_Window *window) {
    for (uint i = 0; i < 8; ++i) {
        bound_buffers[i] = 0;
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
    printf("Deleting OpenGL context...\n");
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

Ref<VertexFormat> Device::create_vertex_format(bool manual_layout) {
    return ref(new VertexFormat(manual_layout));
}

Ref<Mesh> Device::create_mesh(MeshMode mode, uint num_vertex_buffers) {
    return ref(new Mesh(mode, num_vertex_buffers));
}

Ref<Texture> Device::create_texture() {
    return ref(new Texture());
}

Ref<Texture> Device::load_texture(const char *path) {
    Ref<Texture> tex(create_texture());
    tex->load(path);
    return tex;
}

Ref<Texture> Device::load_texture_cubemap(const char *paths[6]) {
    Ref<Texture> tex(create_texture());
    tex->load_cubemap(paths);
    return tex;
}

void Device::clear() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

}


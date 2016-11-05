
static GLenum translateBufferUsage(BufferUsage usage) {
    switch (usage) {
    case BUFFER_USAGE_STATIC_DRAW: return GL_STATIC_DRAW;
    case BUFFER_USAGE_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
    case BUFFER_USAGE_STREAM_DRAW: return GL_STREAM_DRAW;
    default:
        fatal_error("invalid buffer usage type");
        return 0;
    }
}

static GLenum translateBufferAccess(BufferAccess access) {
    switch (access) {
    case BUFFER_ACCESS_READ_ONLY: return GL_READ_ONLY;
    case BUFFER_ACCESS_WRITE_ONLY: return GL_WRITE_ONLY;
    case BUFFER_ACCESS_READ_WRITE: return GL_READ_WRITE;
    default:
        fatal_error("invalid buffer access type");
        return 0;
    }
}

static GLenum translateBufferTarget(BufferTarget target) {
    switch (target) {
    case BUFFER_TARGET_GENERAL0: return GL_COPY_READ_BUFFER;
    case BUFFER_TARGET_GENERAL1: return GL_COPY_WRITE_BUFFER;
    default:
        fatal_error("invalid buffer target type");
        return 0;
    }
}

static GLenum translateShaderType(ShaderType type) {
    switch (type) {
    case SHADER_TYPE_VERTEX: return GL_VERTEX_SHADER;
    case SHADER_TYPE_FRAGMENT: return GL_FRAGMENT_SHADER;
    default:
        fatal_error("invalid shader type");
        return 0;
    }
}


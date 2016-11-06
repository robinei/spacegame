namespace render {

static GLenum from_buffer_target(BufferTarget target) {
    switch (target) {
    case BUFFER_TARGET_READ: return GL_COPY_READ_BUFFER;
    case BUFFER_TARGET_WRITE: return GL_COPY_WRITE_BUFFER;
    case BUFFER_TARGET_VERTEX: return GL_ARRAY_BUFFER;
    case BUFFER_TARGET_INDEX: return GL_ELEMENT_ARRAY_BUFFER;
    case BUFFER_TARGET_UNIFORM: return GL_UNIFORM_BUFFER;
    default:
        fatal_error("invalid buffer target type");
        return 0;
    }
}

static GLenum from_buffer_usage(BufferUsage usage) {
    switch (usage) {
    case BUFFER_USAGE_STATIC_DRAW: return GL_STATIC_DRAW;
    case BUFFER_USAGE_DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
    case BUFFER_USAGE_STREAM_DRAW: return GL_STREAM_DRAW;
    default:
        fatal_error("invalid buffer usage type");
        return 0;
    }
}

static GLenum from_buffer_access(BufferAccess access) {
    switch (access) {
    case BUFFER_ACCESS_READ_ONLY: return GL_READ_ONLY;
    case BUFFER_ACCESS_WRITE_ONLY: return GL_WRITE_ONLY;
    case BUFFER_ACCESS_READ_WRITE: return GL_READ_WRITE;
    default:
        fatal_error("invalid buffer access type");
        return 0;
    }
}

static GLenum from_shader_type(ShaderType type) {
    switch (type) {
    case SHADER_TYPE_VERTEX: return GL_VERTEX_SHADER;
    case SHADER_TYPE_FRAGMENT: return GL_FRAGMENT_SHADER;
    default:
        fatal_error("invalid shader type");
        return 0;
    }
}

static GLenum from_value_type(ValueType type) {
    switch (type) {
    case VALUE_TYPE_SHORT: return GL_SHORT;
    case VALUE_TYPE_USHORT: return GL_UNSIGNED_SHORT;
    case VALUE_TYPE_INT: return GL_INT;
    case VALUE_TYPE_UINT: return GL_UNSIGNED_INT;
    case VALUE_TYPE_FLOAT: return GL_FLOAT;
    default:
        fatal_error("invalid value type");
        return 0;
    }
}

static uint value_type_byte_size(ValueType type) {
    switch (type) {
    case VALUE_TYPE_SHORT: return 2;
    case VALUE_TYPE_USHORT: return 2;
    case VALUE_TYPE_INT: return 4;
    case VALUE_TYPE_UINT: return 4;
    case VALUE_TYPE_FLOAT: return 4;
    default:
        fatal_error("invalid value type");
        return 0;
    }
}

static bool value_type_is_integer(ValueType type) {
    switch (type) {
    case VALUE_TYPE_SHORT:
    case VALUE_TYPE_USHORT:
    case VALUE_TYPE_INT:
    case VALUE_TYPE_UINT:
        return true;
    default:
        return false;
    }
}

static GLenum from_mesh_mode(MeshMode mode) {
    switch (mode) {
    case MESH_POINTS: return GL_POINTS;
    case MESH_LINES: return GL_LINES;
    case MESH_LINE_STRIP: return GL_LINE_STRIP;
    case MESH_TRIANGLES: return GL_TRIANGLES;
    case MESH_TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
    default:
        fatal_error("invalid mesh mode");
        return 0;
    }
}

static GLenum from_texture_target(TextureTarget target) {
    switch (target) {
    case TEXTURE_TARGET_2D: return GL_TEXTURE_2D;
    case TEXTURE_TARGET_CUBE: return GL_TEXTURE_CUBE_MAP;
    default:
        fatal_error("invalid texture target type");
        return 0;
    }
}

}


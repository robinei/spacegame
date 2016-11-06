namespace render {

enum BufferTarget {
    BUFFER_TARGET_INVALID,
    
    BUFFER_TARGET_READ,
    BUFFER_TARGET_WRITE,

    BUFFER_TARGET_VERTEX,
    BUFFER_TARGET_INDEX,
    BUFFER_TARGET_UNIFORM,
};

enum BufferUsage {
    BUFFER_USAGE_STATIC_DRAW,
    BUFFER_USAGE_DYNAMIC_DRAW,
    BUFFER_USAGE_STREAM_DRAW,
};

enum BufferAccess {
    BUFFER_ACCESS_READ_ONLY,
    BUFFER_ACCESS_WRITE_ONLY,
    BUFFER_ACCESS_READ_WRITE,
};

enum ShaderType {
    SHADER_TYPE_VERTEX,
    SHADER_TYPE_FRAGMENT,
};

enum ValueType {
    VALUE_TYPE_SHORT,
    VALUE_TYPE_USHORT,
    VALUE_TYPE_INT,
    VALUE_TYPE_UINT,
    VALUE_TYPE_FLOAT,
};

enum MeshMode {
    MESH_POINTS,
    MESH_LINES,
    MESH_LINE_STRIP,
    MESH_TRIANGLES,
    MESH_TRIANGLE_STRIP,
};

enum TextureTarget {
    TEXTURE_TARGET_INVALID,
    TEXTURE_TARGET_2D,
    TEXTURE_TARGET_CUBE,
};

class Device;
class Shader;
class Program;
class BufferObject;
class VertexFormat;
class Mesh;
class Texture;

}


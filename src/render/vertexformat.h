namespace render {

struct AttribSpec {
    const char *name; // name of this attribute in shader programs
    ValueType type;
    uint count; // 1 for float, up to 4 for vec4
    bool normalized;
};

extern const AttribSpec ATTR_POSITION;
extern const AttribSpec ATTR_NORMAL;
extern const AttribSpec ATTR_TANGENT;
extern const AttribSpec ATTR_BITANGENT;
extern const AttribSpec ATTR_COLOR;
extern const AttribSpec ATTR_UV;

class VertexFormat : public RefCounted {
public:
    struct Attrib {
        AttribSpec spec;
        uint index; // generic vertex attribute index
        uint offset; // byte offset of this attrib within one vertex

        Attrib(const AttribSpec &spec, uint index, uint offset)
            : spec(spec), index(index), offset(offset) { }
    };

    const Attrib &attrib(uint index) const { return _attribs[index]; }

    uint attrib_count() const { return _attribs.size(); }

    uint stride() const { return _stride; }

    // for automatic layout
    void add(uint index, const AttribSpec &spec);

private:
    VertexFormat() : _stride(0) {}
    
    VertexFormat(const VertexFormat &);
    VertexFormat &operator=(const VertexFormat &);
    
    friend class Mesh;
    friend class Device;

    uint _stride;
    PODVector<Attrib> _attribs;
};

}


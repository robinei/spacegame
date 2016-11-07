namespace render {

class VertexFormat : public RefCounted {
public:
    enum Hint {
        // 0 for unknown
        POSITION = 1,
        NORMAL,
        TANGENT,
        BITANGENT,
        COLOR,
        UV,
    };

    struct Attrib {
        uint index;
        Hint hint;
        ValueType type;
        uint count; // 4 for vec4 etc.
        bool normalized;
        uint offset; // auto-calculated unless manual layout
        uint stride; // ignored unless manual layout
    };

    const Attrib &attrib(uint index) const { return _attribs[index]; }

    uint attrib_count() const { return _attribs.size(); }

    uint stride(const Attrib &attrib) {
        return _manual_layout ? attrib.stride : _stride;
    }
    
    // for manual layout
    void add(const Attrib &attrib);

    // for automatic layout
    void add(uint index, Hint hint, ValueType type, uint count,
             bool normalized = false);

private:
    VertexFormat(bool manual_layout);
    
    VertexFormat(const VertexFormat &);
    VertexFormat &operator=(const VertexFormat &);
    
    friend class Mesh;
    friend class Device;

    bool _manual_layout;
    uint _stride;
    PODVector<Attrib> _attribs;
};

}


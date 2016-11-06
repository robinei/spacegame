namespace render {

VertexFormat::VertexFormat(bool manual_layout)
    : _manual_layout(manual_layout), _stride(0) {}

void VertexFormat::add(const Attrib &attrib) {
    assert(_manual_layout);
    assert(!value_type_is_integer(attrib.type) || !attrib.normalized);
    _attribs.push_back(attrib);
}

void VertexFormat::add(uint index, Hint hint, ValueType type, uint count,
                       bool normalized) {
    assert(!_manual_layout);
    assert(!value_type_is_integer(type) || !normalized);
    Attrib attrib;
    attrib.index = index;
    attrib.hint = hint;
    attrib.type = type;
    attrib.count = count;
    attrib.normalized = normalized;
    attrib.offset = _stride;
    _stride += value_type_byte_size(type) * count;
    _attribs.push_back(attrib);
}

}


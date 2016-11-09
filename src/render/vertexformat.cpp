namespace render {

const AttribSpec ATTR_POSITION = { "in_pos", VALUE_TYPE_FLOAT, 4, false };
const AttribSpec ATTR_NORMAL = { "in_normal", VALUE_TYPE_FLOAT, 4, false };
const AttribSpec ATTR_TANGENT = { "in_tangent", VALUE_TYPE_FLOAT, 4, false };
const AttribSpec ATTR_BITANGENT = { "in_bitangent", VALUE_TYPE_FLOAT, 4, false };
const AttribSpec ATTR_COLOR = {"in_color", VALUE_TYPE_FLOAT, 4, false };
const AttribSpec ATTR_UV = { "in_uv", VALUE_TYPE_FLOAT, 2, false };

void VertexFormat::add(uint index, const AttribSpec &spec) {
    assert(!value_type_is_integer(spec.type) || !spec.normalized);
    _stride += value_type_byte_size(spec.type) * spec.count;
    _attribs.push_back(Attrib(spec, index, _stride));
}

}


namespace render {

BufferObject::BufferObject(Device *device) {
    _target = BUFFER_TARGET_INVALID;
    _mapped = false;
    _device = device;
    _size = 0;
    glGenBuffers(1, &_handle);
}

BufferObject::~BufferObject() {
    unbind();
    glDeleteBuffers(1, &_handle);
}

void BufferObject::bind(BufferTarget target) {
    assert(!_mapped);
    if (target == _target) {
        return;
    }
    if (_device->bound_buffers[target]) {
        _device->bound_buffers[target]->unbind();
    }
    glBindBuffer(from_buffer_target(target), target);
    _device->bound_buffers[target] = this;
    _target = target;
}

void BufferObject::unbind() {
    assert(!_mapped);
    if (_target) {
        assert(_device->bound_buffers[_target] == this);
        glBindBuffer(from_buffer_target(_target), 0);
        _device->bound_buffers[_target] = NULL;
        _target = BUFFER_TARGET_INVALID;
    }
}

void BufferObject::data(uint size, const void *data, BufferUsage usage) {
    assert(!_mapped);
    assert(_target);
    _size = size;
    glBufferData(from_buffer_target(_target), size, data, from_buffer_usage(usage));
}

void BufferObject::write(uint offset, uint size, const void *data) {
    assert(!_mapped);
    assert(_target);
    glBufferSubData(from_buffer_target(_target), offset, size, data);
}

void BufferObject::read(uint offset, uint size, void *data) {
    assert(!_mapped);
    assert(_target);
    glGetBufferSubData(from_buffer_target(_target), offset, size, data);
}

void BufferObject::copy(BufferObject *dst, uint readoffset, uint writeoffset, uint size) {
    assert(!_mapped);
    assert(_target);
    assert(dst->_target);
    glCopyBufferSubData(from_buffer_target(_target), from_buffer_target(dst->_target),
                        readoffset, writeoffset, size);
}

void *BufferObject::map(BufferAccess access) {
    assert(_target);
    _mapped = true;
    return glMapBuffer(from_buffer_target(_target), from_buffer_access(access));
}

void *BufferObject::map(uint offset, uint length, BufferAccess access) {
    assert(_mapped);
    assert(_target);
    _mapped = true;
    return glMapBufferRange(from_buffer_target(_target), offset, length, from_buffer_access(access));
}

void BufferObject::flush(uint offset, uint length) {
    assert(_mapped);
    assert(_target);
    glFlushMappedBufferRange(from_buffer_target(_target), offset, length);
}

void BufferObject::unmap() {
    assert(_mapped);
    assert(_target);
    glUnmapBuffer(_target);
    _mapped = false;
}

}


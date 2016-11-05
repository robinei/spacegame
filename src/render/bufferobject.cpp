
BufferObject::BufferObject(Device *device) {
    _target = BUFFER_TARGET_INVALID;
    _pinned_to_target = false;
    _device = device;
    _size = 0;
    glGenBuffers(1, &_handle);
}

BufferObject::~BufferObject() {
    if (_target) {
        _device->unbind(this);
    }
    glDeleteBuffers(1, &_handle);
}

void BufferObject::data(size_t size, const void *data, BufferUsage usage) {
    _device->ensure_bound_to_general_target(this);
    _size = size;
    glBufferData(translateBufferTarget(_target), size, data, translateBufferUsage(usage));
}

void BufferObject::write(size_t offset, size_t size, const void *data) {
    _device->ensure_bound_to_general_target(this);
    glBufferSubData(translateBufferTarget(_target), offset, size, data);
}

void BufferObject::read(size_t offset, size_t size, void *data) {
    _device->ensure_bound_to_general_target(this);
    glGetBufferSubData(translateBufferTarget(_target), offset, size, data);
}

void BufferObject::copy(BufferObject *dst, size_t readoffset, size_t writeoffset, size_t size) {
    _device->ensure_bound_to_general_targets(this, dst);
    glCopyBufferSubData(translateBufferTarget(_target), dst->_target, readoffset, writeoffset, size);
}

void *BufferObject::map(BufferAccess access) {
    _device->ensure_bound_to_general_target(this);
    _pinned_to_target = true;
    return glMapBuffer(translateBufferTarget(_target), translateBufferAccess(access));
}

void *BufferObject::map(size_t offset, size_t length, BufferAccess access) {
    _device->ensure_bound_to_general_target(this);
    _pinned_to_target = true;
    return glMapBufferRange(translateBufferTarget(_target), offset, length, translateBufferAccess(access));
}

void BufferObject::flush(size_t offset, size_t length) {
    assert(_target);
    assert(_pinned_to_target);
    glFlushMappedBufferRange(translateBufferTarget(_target), offset, length);
}

void BufferObject::unmap() {
    assert(_target);
    assert(_pinned_to_target);
    glUnmapBuffer(_target);
    _pinned_to_target = false;
}


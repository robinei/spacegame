
class BufferObject : public RefCounted {
public:
    void data(size_t size, const void *data = 0, BufferUsage usage = BUFFER_USAGE_DYNAMIC_DRAW);
    void write(size_t offset, size_t size, const void *data);
    void read(size_t offset, size_t size, void *data);

    void copy(BufferObject *dst, size_t readoffset, size_t writeoffset, size_t size);

    void *map(BufferAccess access = BUFFER_ACCESS_READ_WRITE);
    void *map(size_t offset, size_t length, BufferAccess access = BUFFER_ACCESS_READ_WRITE);
    void flush(size_t offset, size_t length);
    void unmap();

    size_t size() { return _size; }

protected:
    BufferObject(Device *device);
    ~BufferObject();
    
private:
    BufferObject(const BufferObject &);
    BufferObject &operator=(const BufferObject &);

    friend class Device;

    Device *_device;
    BufferTarget _target;
    bool _pinned_to_target;
    
    size_t _size;
    unsigned int _handle;
};


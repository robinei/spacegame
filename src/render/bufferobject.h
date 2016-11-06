namespace render {

class BufferObject : public RefCounted {
public:
    void bind(BufferTarget target);
    void unbind();
    
    void data(uint size, const void *data = 0, BufferUsage usage = BUFFER_USAGE_DYNAMIC_DRAW);
    void write(uint offset, uint size, const void *data);
    void read(uint offset, uint size, void *data);

    void copy(BufferObject *dst, uint readoffset, uint writeoffset, uint size);

    void *map(BufferAccess access = BUFFER_ACCESS_READ_WRITE);
    void *map(uint offset, uint length, BufferAccess access = BUFFER_ACCESS_READ_WRITE);
    void flush(uint offset, uint length);
    void unmap();

    uint size() { return _size; }

protected:
    BufferObject(Device *device);
    ~BufferObject();
    
private:
    BufferObject(const BufferObject &);
    BufferObject &operator=(const BufferObject &);

    friend class Device;

    Device *_device;
    BufferTarget _target;
    bool _mapped;
    
    uint _size;
    uint _handle;
};

}


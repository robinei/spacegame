#ifndef REFCOUNTED_H
#define REFCOUNTED_H

class RefCounted {
protected:
    RefCounted() : m_refcount(0) {}
    virtual ~RefCounted() {}

private:
    template <class T> friend class Ref;

    void addref() {
        ++m_refcount;
    }

    void release() {
        if (--m_refcount <= 0)
            delete this;
    }

    mutable int m_refcount;
};

template <class T>
class Ref {
    T *_ptr;
    
public:
    Ref() : _ptr(0) {}

    Ref(T *ptr) : _ptr(ptr) {
        ptr->addref();
    }
    
    Ref(const Ref &ref) : _ptr(ref._ptr) {
        _ptr->addref();
    }

    ~Ref() {
        if (_ptr)
            _ptr->release();
    }

    Ref &operator=(T *ptr) {
        if (_ptr != ptr) {
            T *temp = _ptr;
            _ptr = ptr;
            if (ptr)
                ptr->addref();
            if (temp)
                temp->release();
        }
        return *this;
    }
    
    Ref &operator=(const Ref &ref) {
        return (*this = ref._ptr);
    }
    
    T *ptr() { return _ptr; }
    const T *ptr() const { return _ptr; }

    T *operator*() { return _ptr; }
    const T *operator*() const { return _ptr; }

    T *operator->() { return _ptr; }
    const T *operator->() const { return _ptr; }

    operator bool() const { return !!_ptr; }
    
    bool operator==(T *ptr) const { return _ptr == ptr; }
    bool operator!=(T *ptr) const { return _ptr != ptr; }
    bool operator==(const Ref &ref) const { return _ptr == ref._ptr; }
    bool operator!=(const Ref &ref) const { return _ptr != ref._ptr; }
};

#endif

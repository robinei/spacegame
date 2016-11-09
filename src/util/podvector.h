
template<typename T>
class PODVector {
    size_t count;
    size_t capacity;
    T *data;
    
public:
    PODVector() : count(0), capacity(0), data(NULL) {
    }
    
    PODVector(size_t initial_count) : count(0), capacity(0), data(NULL) {
        resize(initial_count);
    }

    PODVector(const PODVector &v) : count(0), capacity(0), data(NULL) {
        *this = v;
    }

    ~PODVector() {
        free(data);
    }

    PODVector &operator=(const PODVector &v) {
        resize(v.count);
        if (count) {
            memcpy(data, v.data, sizeof(T) * count);
        }
    }
    
    uint size() const {
        return count;
    }

    bool empty() {
        return count == 0;
    }

    T back() const {
        assert(count > 0);
        return data[count - 1];
    }
    
    const T &at(uint i) const {
        assert(i < count);
        return data[i];
    }

    const T &operator[](uint i) const {
        assert(i < count);
        return data[i];
    }

    T &operator[](uint i) {
        assert(i < count);
        return data[i];
    }

    void clear() {
        count = 0;
    }

    void resize(uint new_count) {
        count = new_count;
        if (count <= capacity) {
            return;
        }
        while (new_count > capacity) {
            capacity = capacity ? capacity * 2 : 16;
        }
        data = (T *)realloc(data, sizeof(T) * capacity);
    }

    void reserve(uint new_capacity) {
        if (new_capacity > capacity) {
            capacity = new_capacity;
            data = (T *)realloc(data, sizeof(T) * capacity);
        }
    }

    void push_back(T value) {
        if (count == capacity) {
            capacity = capacity ? capacity * 2 : 16;
            data = (T *)realloc(data, sizeof(T) * capacity);
        }
        data[count++] = value;
    }

    void pop_back() {
        assert(count > 0);
        --count;
    }
};


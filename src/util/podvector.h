
template<typename T>
class PODVector {
    size_t count;
    size_t capacity;
    T *data;
    
    PODVector(const PODVector &);
    PODVector &operator=(const PODVector &);
    
public:
    PODVector() : count(0), capacity(0), data(NULL) {
    }
    
    PODVector(size_t initial_capacity) : count(0), capacity(0), data(NULL) {
        resize(initial_capacity);
    }

    ~PODVector() {
        free(data);
    }

    size_t size() const {
        return count;
    }

    bool empty() {
        return count == 0;
    }

    T back() const {
        assert(count > 0);
        return data[count - 1];
    }
    
    const T &at(size_t i) const {
        assert(i < count);
        return data[i];
    }

    const T &operator[](size_t i) const {
        assert(i < count);
        return data[i];
    }

    T &operator[](size_t i) {
        assert(i < count);
        return data[i];
    }

    void clear() {
        count = 0;
    }

    void resize(size_t new_count) {
        count = new_count;
        while (new_count > capacity) {
            capacity = capacity ? capacity * 2 : 16;
        }
        data = (T *)realloc(data, sizeof(T) * capacity);
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


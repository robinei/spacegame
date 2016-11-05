
// https://github.com/jzebedee/rhbackshiftdict/blob/master/src/robinhood/RobinHoodDictionary.cs
// https://github.com/goossaert/hashmap/blob/master/backshift_hashmap.cc
// http://codecapsule.com/2013/11/17/robin-hood-hashing-backward-shift-deletion/

template<
    typename TKey,
    typename TValue,
    typename THashFunc = Hash<TKey>,
    typename TEqualFunc = Equal<TKey>
>
class HashTable {
    struct Entry {
        uint32_t hash;
        TKey key;
        TValue value;

        Entry(uint32_t hash, TKey key, TValue value)
        : hash(hash), key(key), value(value) {}
    };

    uint32_t used;
    uint32_t size;
    Entry *entries;

    HashTable(const HashTable &); // disallow
    HashTable &operator=(const HashTable &); // disallow

public:
    HashTable(uint32_t size = 16) {
        used = 0;
        resize(next_pow2(size));
    }

    ~HashTable() {
        free(entries);
    }

    bool get(TKey key, TValue &value_out) {
        uint32_t index;
        if (find(key, index)) {
            value_out = entries[index].value;
            return true;
        }
        return false;
    }

    void put(TKey key, TValue value) {
        if ((float)used / size > 0.85f) {
            resize(size * 2);
        }
        put(Entry(calc_hash(key), key, value));
    }

    bool remove(TKey key) {
        uint32_t index;
        if (!find(key, index)) {
            return false;
        }

        for (uint32_t i = 0; i < size; ++i) {
            uint32_t curr_index = (index + i) & (size - 1);
            uint32_t next_index = (index + i + 1) & (size - 1);

            uint32_t next_hash = entries[next_index].hash;
            if (next_hash == 0 || dist_to_start(next_hash, next_index) == 0) {
                entries[curr_index].hash = 0;
                --used; // TODO: shrink
                return true;
            }

            swap(entries[curr_index], entries[next_index]);
        }

        assert(0 && "control flow should not get here");
        return false;
    }

private:
    void put(Entry entry) {
        uint32_t start_index = entry.hash & (size - 1);
        uint32_t probe = 0;

        for (uint32_t i = 0; i < size; ++i, ++probe) {
            uint32_t index = (start_index + i) & (size - 1);
            Entry &slot = entries[index];

            if (slot.hash == 0) {
                ++used;
                slot = entry;
                return;
            }

            if (slot.hash == entry.hash && TEqualFunc()(slot.key, entry.key)) {
                slot.value = entry.value;
                return;
            }

            uint32_t slot_probe = dist_to_start(slot.hash, index);
            if (probe > slot_probe) {
                probe = slot_probe;
                swap(slot, entry);
            }
        }
    }

    bool find(TKey key, uint32_t &index_out) const {
        if (used == 0) {
            return false;
        }
        uint32_t hash = calc_hash(key);
        uint32_t start_index = hash & (size - 1);
        uint32_t probe = 0;

        for (uint32_t i = 0; i < size; ++i, ++probe) {
            uint32_t index = (start_index + i) & (size - 1);
            Entry &slot = entries[index];

            if (slot.hash == hash && TEqualFunc()(slot.key, key)) {
                index_out = index;
                return true;
            }

            if (slot.hash != 0) {
                probe = dist_to_start(slot.hash, index);
            }

            if (i > probe) {
                break;
            }
        }
        return false;
    }

    void resize(uint32_t new_size) {
        uint32_t old_used = used;
        uint32_t old_size = size;
        Entry *old_entries = entries;

        used = 0;
        size = new_size;
        entries = (Entry *)calloc(1, sizeof(Entry) * new_size);

        if (old_used) {
            assert(old_used <= new_size);

            for (uint32_t i = 0; i < old_size; ++i) {
                Entry &slot = old_entries[i];
                if (slot.hash) {
                    put(slot);
                }
            }

            free(old_entries);
        }
    }

    uint32_t dist_to_start(uint32_t hash, uint32_t index_stored) const {
        assert(hash != 0);
        uint32_t start_index = hash & (size - 1);
        if (start_index <= index_stored) {
            return index_stored - start_index;
        }
        return index_stored + (size - start_index);
    }

    static uint32_t calc_hash(TKey key) {
        uint32_t hash = THashFunc()(key);
        return hash ? hash : 1;
    }

    static uint32_t next_pow2(uint32_t v) {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    // TODO: use C++ 11 and move semantics?
    template<typename T>
    static void swap(T &a, T &b) {
        T temp(a);
        a = b;
        b = temp;
    }
};

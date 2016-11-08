
struct Vec3 {
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(Vec2 v, float z = 0) : x(v.x), y(v.y), z(z) {}
    Vec3(float x, float y, float z = 0) : x(x), y(y), z(z) {}
    
    float &operator[](int i) {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }
    const float &operator[](int i) const {
        assert(i >= 0 && i < 3);
        return (&x)[i];
    }

    Vec2 xy() { return Vec2(x, y); }

    Vec3 &operator+=(Vec3 v);
    
    static Vec3 zero() { return Vec3(0, 0, 0); }
    static Vec3 unit_x() { return Vec3(1, 0, 0); }
    static Vec3 unit_y() { return Vec3(0, 1, 0); }
    static Vec3 unit_z() { return Vec3(0, 0, 1); }
    static Vec3 scale_identity() { return Vec3(1, 1, 1); }
};

inline Vec3 operator +(Vec3 a, Vec3 b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec3 operator -(Vec3 a, Vec3 b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 operator *(Vec3 v, float f) { return Vec3(v.x * f, v.y * f, v.z * f); }
inline Vec3 operator *(float f, Vec3 v) { return Vec3(f * v.x, f * v.y, f * v.z); }
inline Vec3 operator *(Vec3 a, Vec3 b) { return Vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline Vec3 operator /(Vec3 a, Vec3 b) { return Vec3(a.x / b.x, a.y / b.y, a.z / b.z); }
inline Vec3 operator /(Vec3 v, float f) { return v * (1.f / f); }

inline Vec3 &Vec3::operator+=(Vec3 v) { *this = *this * v; return *this; }

inline float sqr_length(Vec3 v) { return v.x * v.x + v.y * v.y + v.z * v.z; }
inline float length(Vec3 v) { return sqrtf(sqr_length(v)); }
inline Vec3 normalize
(Vec3 v) { return v * (1.f / length(v)); }
inline Vec3 abs(Vec3 v) { return Vec3(fabs(v.x), fabs(v.y), fabs(v.z)); }
inline Vec3 inverse(Vec3 v) { return Vec3(1.f / v.x, 1.f / v.y, 1.f / v.z); }
inline float dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline float angle(Vec3 a, Vec3 b) { return acosf(dot(a, b) / (length(a) * length(b))); }
inline Vec3 cross(Vec3 a, Vec3 b) { return Vec3(a.y * b.z - a.z * b.y,
                                                a.z * b.x - a.x * b.z,
                                                a.x * b.y - a.y * b.x); }


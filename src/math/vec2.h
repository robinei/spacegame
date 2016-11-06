
struct Vec2 {
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    float &operator[](int i) {
        assert(i >= 0 && i < 2);
        return (&x)[i];
    }
    const float &operator[](int i) const {
        assert(i >= 0 && i < 2);
        return (&x)[i];
    }

    static Vec2 zero() { return Vec2(0, 0); }
    static Vec2 unit_x() { return Vec2(1, 0); }
    static Vec2 unit_y() { return Vec2(0, 1); }
    static Vec2 scale_identity() { return Vec2(1, 1); }
};

inline Vec2 operator +(Vec2 a, Vec2 b) { return Vec2(a.x + b.x, a.y + b.y); }
inline Vec2 operator -(Vec2 a, Vec2 b) { return Vec2(a.x - b.x, a.y - b.y); }
inline Vec2 operator *(Vec2 v, float f) { return Vec2(v.x * f, v.y * f); }
inline Vec2 operator *(float f, Vec2 v) { return Vec2(f * v.x, f * v.y); }
inline Vec2 operator *(Vec2 a, Vec2 b) { return Vec2(a.x * b.x, a.y * b.y); }
inline Vec2 operator /(Vec2 a, Vec2 b) { return Vec2(a.x / b.x, a.y / b.y); }
inline Vec2 operator /(Vec2 v, float f) { return v * (1.f / f); }

inline float sqr_length(Vec2 v) { return v.x * v.x + v.y * v.y; }
inline float length(Vec2 v) { return sqrtf(sqr_length(v)); }
inline Vec2 normalized(Vec2 v) { return v * (1.f / length(v)); }
inline Vec2 abs(Vec2 v) { return Vec2(fabs(v.x), fabs(v.y)); }
inline Vec2 inverse(Vec2 v) { return Vec2(1.f / v.x, 1.f / v.y); }
inline float dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }
inline float angle(Vec2 a, Vec2 b) { return acosf(dot(a, b) / (length(a) * length(b))); }



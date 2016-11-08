class FPSCamera {
public:
    FPSCamera() {
        _up = Vec3(0, 1, 0);
    }

    void set_pos(Vec3 pos) {
        _pos = pos;
    }

    void set_dir(Vec3 dir) {
        _dir = dir;
    }

    void look_at(Vec3 target) {
        _dir = normalize(target - _pos);
    }

    Vec3 pos() {
        return _pos;
    }

    Vec3 dir() {
        return _dir;
    }

    void step(float amount) {
        _pos += _dir * amount;
    }

    void strafe(float amount) {
        Vec3 side = normalize(cross(_dir, _up));
        _pos += side * amount;
    }

    void rise(float amount) {
        Vec3 side = normalize(cross(_dir, _up));
        Vec3 up = normalize(cross(side, _dir));
        _pos += up * amount;
    }

    void rotate(float yaw, float pitch) {
        Vec3 side = normalize(cross(_dir, _up));
        _dir = Quat::from_axis_angle(_up, yaw) * _dir;
        _dir = Quat::from_axis_angle(side, pitch) * _dir;
    }

    void view_matrix(Mat4 &m) {
        /*return glm::lookAt(
            _pos,
            _pos + _dir,
            _up
            );*/
    }

private:
    Vec3 _up;
    Vec3 _pos;
    Vec3 _dir;
};


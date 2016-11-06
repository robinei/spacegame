namespace render {

class Texture : public RefCounted {
public:
    void bind(int texture_unit, TextureTarget target = TEXTURE_TARGET_2D);
    void unbind();

    void load(const char *path);
    void load_cubemap(const char *paths[6]);

private:
    Texture();
    ~Texture();

    Texture(const Texture &);
    Texture &operator=(const Texture &);

    friend class Device;

    TextureTarget bound_target;
    uint handle;
};

}


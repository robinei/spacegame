#include "stb_image.h"

namespace render {

Texture::Texture() : bound_target(TEXTURE_TARGET_INVALID) {
    glGenTextures(1, &handle);
}

Texture::~Texture() {
    glDeleteTextures(1, &handle);
}

void Texture::bind(int texture_unit, TextureTarget target) {
    assert(!bound_target);
    assert(texture_unit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    bound_target = target;
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(from_texture_target(target), handle);
}

void Texture::unbind() {
    assert(bound_target);
    glBindTexture(bound_target, 0);
    bound_target = TEXTURE_TARGET_INVALID;
}

void Texture::load(const char *path) {
    bind(0);

    int width, height, comp;
    stbi_uc *data = stbi_load(path, &width, &height, &comp, 3);
    assert(data);
    assert(comp == 3);

    glTexImage2D(bound_target, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    free(data);

    glTexParameteri(bound_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(bound_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    unbind();
}

void Texture::load_cubemap(const char *paths[6]) {
    GLenum targets[6] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    bind(0, TEXTURE_TARGET_CUBE);

    for (int i = 0; i < 6; ++i) {
        int width, height, comp;
        stbi_uc *data = stbi_load(paths[i], &width, &height, &comp, 3);
        assert(data);
        assert(comp == 3);

        glTexImage2D(targets[i], 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

        free(data);

        glTexParameteri(bound_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(bound_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(bound_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(bound_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(bound_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    unbind();
}

}


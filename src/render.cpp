#include "common.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "stb_image.h"
#include "rply.h"

#include "util/refcounted.h"
#include "util/podvector.h"
#include "math/math.h"

#include "render/render.h"

#include "render/util.cpp"
#include "render/device.cpp"
#include "render/shader.cpp"
#include "render/program.cpp"
#include "render/bufferobject.cpp"
#include "render/vertexformat.cpp"
#include "render/mesh.cpp"
#include "render/texture.cpp"
#include "render/plyloader.cpp"

namespace render {

void init_sdl_hints() {
    bool ok = true;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4) == 0;
    ok = ok && SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1) == 0;
    if (!ok)
        fatal_error("SDL_GL_SetAttribute() error: %s", SDL_GetError());
}

}


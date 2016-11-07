#include "../deps/deps.h"

#include "common.h"

#include "stdstub.cpp"

#include "SDL2/SDL.h"
#ifdef WIN32
#include <Windows.h>
#endif

#include "util/pair.h"
#include "util/refcounted.h"
#include "util/arena.h"
#include "util/functors.h"
#include "util/podvector.h"
#include "util/hashtable.h"
#include "util/intrusive_link.h"
#include "util/intrusive_list.h"
#include "util/intrusive_hashtable.h"
#include "math/math.h"
#include "render/render.h"


int main(int argc, char *argv[]) {
#ifdef WIN32
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CON", "w", stdout);
        freopen("CON", "w", stderr);
    }
#endif
    printf("Starting...\n");
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        fatal_error("SDL_Init() error: %s", SDL_GetError());

    render::init_sdl_hints();
    
    SDL_DisplayMode mode;
    if (SDL_GetDesktopDisplayMode(0, &mode) < 0)
        fatal_error("SDL_GetDesktopDisplayMode() error: %s", SDL_GetError());
    //mode.w = 1920, mode.h = 1080;

    SDL_Window *window = SDL_CreateWindow(
        "Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mode.w, mode.h,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
        );
    if (!window)
        fatal_error("SDL_CreateWindow() error: %s", SDL_GetError());

    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    	fatal_error("SDL_SetWindowFullscreen() error: %s", SDL_GetError());

    Ref<render::Device> device(render::Device::create(window));

    render::PlyLoader ply_loader(device.ptr());
    Ref<render::Mesh> sphere(ply_loader.load("assets/sphere.ply"));
    printf("num_indexes: %d\n", (int)sphere->num_indexes());

    bool running = false;
    while (running) {
        device->clear();
        SDL_GL_SwapWindow(window);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEWHEEL:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            case SDL_QUIT:
                running = false;
                break;
            }
        }
    }

    printf("Deleting render device...\n");
    device = NULL;
    printf("Destroying window...\n");
    SDL_DestroyWindow(window);
    printf("Shutting down SDL...\n");
    SDL_Quit();
    printf("Done.\n");
    return 0;
}


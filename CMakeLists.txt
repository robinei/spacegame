cmake_minimum_required (VERSION 2.8.8)
project (SpaceGame)

set(COMMON_FLAGS "-Wno-unused-variable -Wno-unused-function -DYAML_DECLARE_STATIC")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -std=c++98 -fno-exceptions -fno-rtti")

file(GLOB_RECURSE DEPS_SOURCES deps/*.cpp deps/*.c)

add_library(deps STATIC ${DEPS_SOURCES})
target_include_directories(deps PRIVATE deps)

add_library(render OBJECT src/render/render.cpp)
target_include_directories(render PRIVATE deps)
target_include_directories(render PRIVATE src)
target_compile_options(render PUBLIC -Wall)

add_executable(main src/main.cpp $<TARGET_OBJECTS:render>)
target_include_directories(main PRIVATE deps)
target_include_directories(main PRIVATE src)
target_link_libraries(main deps m rt pthread dl SDL2 SDLmain GL)
target_compile_options(main PUBLIC -Wall)


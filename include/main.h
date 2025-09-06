// #pragma once
// // #define SDL_MAIN_USE_CALLBACKS  // This is necessary for the new callbacks API. To use the legacy API, don't define this. 
// #include <SDL3/SDL.h>
// // #include <SDL3/SDL_main.h>
// // #include <SDL3/SDL_init.h>
// #include <SDL3_ttf/SDL_ttf.h>
// #include <SDL3_mixer/SDL_mixer.h>
// #include <SDL3_image/SDL_image.h>
// #include <cmath>
// #include <string_view>
// #include <filesystem>
// #include <thread>

#pragma once
#include "game.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

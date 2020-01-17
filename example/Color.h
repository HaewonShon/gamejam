#pragma once
#include <SDL2/SDL.h>

namespace Color
{
    constexpr SDL_Color BLACK       = { 0, 0, 0, 255 };
    constexpr SDL_Color WHITE       = { 255, 255, 255, 255 };
    constexpr SDL_Color RED         = { 255, 0, 0, 255 };
    constexpr SDL_Color GREEN       = { 34, 140, 67, 255 };
    constexpr SDL_Color BLUE        = { 0, 0, 255, 255 };
    constexpr SDL_Color GREY        = { 136, 136, 136, 255 };
    constexpr SDL_Color WALLGREY    = { 127, 125, 103, 255 };

    constexpr SDL_Color CORAL_RED   = { 255, 68, 68, 255 };
    constexpr SDL_Color BROWN       = { 134, 102, 74, 255 };
    constexpr SDL_Color SKY         = { 135, 192, 235, 255 };
}

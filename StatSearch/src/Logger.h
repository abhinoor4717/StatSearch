#pragma once

#include "SDL3/SDL.h"

#define LOG_ERROR(fmt, ...) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) SDL_LogTrace(SDL_LOG_CATEGORY_APPLICATION, fmt, ##__VA_ARGS__)
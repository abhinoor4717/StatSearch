#pragma once

#include "SDL3/SDL.h"

class Event {
public:
    Event(SDL_Event& e) : NativeEvent(e), Handled(false) {}
    
    SDL_Event& NativeEvent;
    bool Handled = false;
};
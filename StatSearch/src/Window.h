#pragma once

#include "SDL3/SDL.h"
#include <string>

class Window {
public:
    Window(const char* title, unsigned int w, unsigned int h);
    ~Window();

    inline SDL_Window* GetNativeWindow() { return m_NativeWindow; }
    inline SDL_Renderer* GetNativeRenderer() { return m_NativeRenderer; }
    inline unsigned int GetWidth() { return m_Width; }
    inline unsigned int GetHeight() { return m_Height; }
    inline std::string GetTitle() { return m_Title; }

    inline void SetResizeable(bool resizeable) { SDL_SetWindowResizable(m_NativeWindow, resizeable); }
    void SetWidth(unsigned int w);
    void SetHeight(unsigned int h);

    void OnResize(unsigned int w, unsigned int h);

private:
    std::string m_Title;
    unsigned int m_Width;
    unsigned int m_Height;
    SDL_Window* m_NativeWindow;
    SDL_Renderer* m_NativeRenderer;
};
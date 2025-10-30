#include "Window.h"
#include "Logger.h"

Window::Window(const char* title, unsigned int w, unsigned int h)
    : m_Title(title), m_Width(w), m_Height(h) {
        m_NativeWindow = SDL_CreateWindow(title, w, h, 0);
        if (!m_NativeWindow) {
            LOG_ERROR("Could not create window: %s", SDL_GetError());
            exit(-1);
        }
        m_NativeRenderer = SDL_CreateRenderer(m_NativeWindow, NULL);
        if (!m_NativeRenderer) {
            LOG_ERROR("Could not create window: %s", SDL_GetError());
            exit(-1);
        }
    }

Window::~Window() {
    SDL_DestroyRenderer(m_NativeRenderer);
    SDL_DestroyWindow(m_NativeWindow);
}

void Window::SetWidth(unsigned int w) {
    m_Width = w;
    SDL_SetWindowSize(m_NativeWindow, w, m_Height);
}

void Window::SetHeight(unsigned int h) {
    m_Height = h;
    SDL_SetWindowSize(m_NativeWindow, m_Width, h);
}

void Window::OnResize(unsigned int w, unsigned int h) {
    m_Width = w;
    m_Height = h;
}
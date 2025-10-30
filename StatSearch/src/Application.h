#pragma once

#include <memory>
#include <string>
#include "Window.h"
#include "Event.h"

class Application {
public:
    Application(const char* title, unsigned int w, unsigned int h);
    ~Application();

    virtual void OnUpdate(float dt);
    virtual void OnRender();
    virtual void OnImGuiRender();

    virtual void OnEvent(Event& event);

    void Run();

    inline Window& GetWindow() { return *m_Window; }
    inline SDL_Renderer* GetNativeRenderer() { return m_Window->GetNativeRenderer(); }



private:
    std::string m_Title;
    bool m_Running;
    std::unique_ptr<Window> m_Window;
};
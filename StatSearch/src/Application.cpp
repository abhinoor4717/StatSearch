#include "Application.h"
#include "Logger.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "backends/imgui_impl_sdlrenderer3.h"

Application::Application(const char* title, unsigned int w, unsigned int h)
    : m_Title(title), m_Running(false) {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            LOG_ERROR("Could not initialize SDL: %s", SDL_GetError());
            exit(-1);
        }

        SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);

        m_Window = std::make_unique<Window>(title, w, h);
        
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        io.Fonts->AddFontFromFileTTF("../StatSearch/assets/fonts/Inter.ttc", 0.0f, nullptr, io.Fonts->GetGlyphRangesDefault());

        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        style.FontScaleDpi = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
        style.ScaleAllSizes(SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay()));
        io.FontGlobalScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

        ImGui_ImplSDL3_InitForSDLRenderer(m_Window->GetNativeWindow(), m_Window->GetNativeRenderer());
        ImGui_ImplSDLRenderer3_Init(m_Window->GetNativeRenderer());

        m_Running = true;
}

Application::~Application() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    m_Window.reset();
    SDL_Quit();
}

void Application::Run() {
    SDL_Event e;

    Uint64 frequency = SDL_GetPerformanceFrequency();
    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 last_time = 0;

    while (m_Running) {
        while (SDL_PollEvent(&e)) {
            ImGui_ImplSDL3_ProcessEvent(&e);

            Event event(e);
            OnEvent(event);

            if (event.Handled) continue;
            if (e.type == SDL_EVENT_QUIT) {
                m_Running = false;
            }
            else if (e.type == SDL_EVENT_WINDOW_RESIZED) {
                m_Window->OnResize(e.window.data1, e.window.data2);
            }
        }

        // Calculate deltatime
        last_time = current_time;
        current_time = SDL_GetPerformanceCounter();
        float dt = (float)(current_time - last_time) / frequency;

        OnUpdate(dt);
        
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        
        OnRender();
        OnImGuiRender();

        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_Window->GetNativeRenderer());
        SDL_RenderPresent(m_Window->GetNativeRenderer());
    }
}

void Application::OnUpdate(float dt) {

}

void Application::OnRender() {
    SDL_SetRenderDrawColor(m_Window->GetNativeRenderer(), 0, 0, 0, 255);
    SDL_RenderClear(m_Window->GetNativeRenderer());
}

void Application::OnImGuiRender() {

}

void Application::OnEvent(Event& e) {
    
}
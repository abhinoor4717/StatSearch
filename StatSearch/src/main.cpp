#include "Application.h"
#include "imgui.h"
#include "Logger.h"

class StatSearch : public Application {
public:
    StatSearch() : Application("StatSearch", 800, 600) {
        GetWindow().SetResizeable(true);
    }

    void OnImGuiRender() override { 
        {
            ImGuiIO& io = ImGui::GetIO();

            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(io.DisplaySize);

            ImGuiWindowFlags window_flags =
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoDecoration |
                ImGuiWindowFlags_NoSavedSettings |
                ImGuiWindowFlags_NoBringToFrontOnFocus |
                ImGuiWindowFlags_NoNavFocus;

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

            if (ImGui::Begin("StatSearch", nullptr, window_flags)) {
                float windowWidth = ImGui::GetWindowSize().x;
                ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("StatSearch").x) * 0.5f);
                ImGui::TextColored(ImVec4(1.0f, 0.8f, 1.0f, 1.0f), "StatSearch");

                ImGui::Separator();

                ImGui::Dummy(ImVec2(0, 10));
                
            }
            ImGui::End();

            ImGui::PopStyleVar();
        }
    }
};

int main(int argc, char* argv[]) {
    StatSearch app;
    app.Run();
}
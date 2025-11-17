#include "Application.h"
#include "imgui.h"
#include "Logger.h"
#include <iostream>

#include "httplib.h"
#include "nlohmann/json.hpp"
#include "StatSearchAPI/api.h"

using json = nlohmann::json;

class StatSearch : public Application {
public:
    StatSearch() : Application("StatSearch", 800, 600) {
        GetWindow().SetResizeable(true);

        StatSearchAPI::Greet();

        // httplib::Client cli("http://jsonplaceholder.typicode.com");

        // auto res = cli.Get("/posts/1");
        // if (res) {
        //     json data = json::parse(res->body);
        // } else {
        //     std::cout << "Request failed!\n";
        // }
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

                {
                    static char searchBuf[32];
                    static const char* leagues[] = { "NBA", "WNBA", "NFL", "NHL", "MLB" };
                    static unsigned int selectedLeague = 0;

                    // Calculate total available width
                    float totalWidth = ImGui::GetContentRegionAvail().x;

                    // Define relative widths
                    float dropdownWidth = totalWidth * 0.2f;   // 20% for dropdown
                    float buttonWidth   = totalWidth * 0.15f;  // 15% for button
                    float inputWidth    = totalWidth - dropdownWidth - buttonWidth - 10.0f; // remaining width minus spacing

                    // Dropdown
                    ImGui::PushItemWidth(dropdownWidth);
                    if (ImGui::BeginCombo("##League", leagues[selectedLeague])) {
                        for (int i = 0; i < IM_ARRAYSIZE(leagues); i++) {
                            bool isSelected = (selectedLeague == i);
                            if (ImGui::Selectable(leagues[i], isSelected))
                                selectedLeague = i;
                            if (isSelected)
                                ImGui::SetItemDefaultFocus();
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::PopItemWidth();

                    ImGui::SameLine();

                    // Search input
                    ImGui::PushItemWidth(inputWidth);
                    ImGui::InputTextWithHint("##SearchBar", "Enter a player", searchBuf, IM_ARRAYSIZE(searchBuf));
                    ImGui::PopItemWidth();

                    ImGui::SameLine();

                    // Search button
                    if (ImGui::Button("Search", ImVec2(buttonWidth, 0))) {
                        std::cout << "Searching for: " << searchBuf << " in " << leagues[selectedLeague] << std::endl;
                    }

                }
                
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
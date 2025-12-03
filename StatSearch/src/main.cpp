#include "Application.h"
#include "imgui.h"
#include "Logger.h"
#include <iostream>

#include "nlohmann/json.hpp"
#include "StatSearchAPI/api.h"

using json = nlohmann::json;

class StatSearch : public Application {
public:
    StatSearch() : Application("StatSearch", 1080, 720) {
        GetWindow().SetResizeable(true);
        GetWindow().SetMaximized(true);
        m_Players.emplace_back("Lebron James", 10000000, "Forward", 40, 0, "t", 67, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
        m_Players.emplace_back("Stephen Curry", 10000000, "Forward", 40, 0, "t", 41, 0, 0, 0, 0, 0, 0, 0);
    }

    void OnImGuiRender() override {
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

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.12f, 1.0f));

        if (ImGui::Begin("StatSearch", nullptr, window_flags))
        {
            float windowWidth = ImGui::GetWindowSize().x;
            float contentWidth = ImGui::GetContentRegionAvail().x;

            // ---- HEADER ---- //
            {
                ImGui::PushFont(io.Fonts->Fonts[0]); // Use default font

                ImGui::Spacing();
                ImGui::Spacing();

                // Title with gradient-like color
                const char* title = "StatSearch";
                ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize(title).x) * 0.5f);
                ImGui::TextColored(ImVec4(0.3f, 0.7f, 1.0f, 1.0f), title);

                ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize("Your Basketball Stats Database").x) * 0.5f);
                ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.6f, 1.0f), "Your Basketball Stats Database");

                ImGui::PopFont();

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
            }

            static std::vector<StatSearchAPI::Player> playerResults = m_Players;
            static char searchBuf[128] = "";

            // ---- SEARCH BAR ---- //
            {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(12, 10));
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.2f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.2f, 0.2f, 0.25f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.25f, 0.25f, 0.3f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.5f, 0.9f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.6f, 1.0f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.15f, 0.4f, 0.8f, 1.0f));

                // Recalculate search bar width each frame
                float currentContentWidth = ImGui::GetContentRegionAvail().x;
                float maxSearchWidth = 800.0f;
                float searchBarWidth = currentContentWidth > maxSearchWidth ? maxSearchWidth : currentContentWidth - 40;
                float leftPadding = (currentContentWidth - searchBarWidth) * 0.5f;

                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + leftPadding);
                ImGui::BeginGroup();

                // Responsive button sizing
                float inputWidth = searchBarWidth * 0.68f;
                float buttonWidth = searchBarWidth * 0.27f;
                float spacing = searchBarWidth * 0.05f;

                ImGui::PushItemWidth(inputWidth);
                ImGui::InputTextWithHint("##SearchBar", "Search player by name...", searchBuf, IM_ARRAYSIZE(searchBuf));
                ImGui::PopItemWidth();

                ImGui::SameLine(0, spacing);

                if (ImGui::Button("Search", ImVec2(buttonWidth, 0))) {
                    if (!std::string(searchBuf).empty()) {
                        auto player = StatSearchAPI::Search::searchByName(m_Players, searchBuf);
                        playerResults.clear();
                        playerResults.push_back(player);
                    }
                }

                ImGui::EndGroup();

                ImGui::PopStyleColor(6);
                ImGui::PopStyleVar(2);

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Spacing();
            }

            // ---- PLAYER CARDS CONTAINER ---- //
            ImGui::BeginChild("PlayerCardsRegion", ImVec2(0, 0), false);

            for (size_t i = 0; i < playerResults.size(); i++)
            {
                auto& p = playerResults[i];

                // Get available width and calculate responsive layout
                float availableWidth = ImGui::GetContentRegionAvail().x;

                // Determine responsive column layout based on window width
                int numColumns = 3;
                if (availableWidth < 700.0f) numColumns = 2;
                if (availableWidth < 450.0f) numColumns = 1;

                // Card background with padding
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.18f, 0.95f));
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 15));
                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.4f, 0.4f));

                std::string cardID = "PlayerCard_" + std::to_string(i);

                // Calculate needed height based on number of columns
                float baseLineHeight = ImGui::GetTextLineHeightWithSpacing();
                float cardHeight = baseLineHeight * 7.0f + 60.0f; // header + stats + padding
                if (numColumns == 2) cardHeight = baseLineHeight * 10.0f + 60.0f;
                if (numColumns == 1) cardHeight = baseLineHeight * 14.0f + 60.0f;

                // Use full available width for the card
                ImGui::BeginChild(cardID.c_str(), ImVec2(availableWidth, cardHeight), true);

                // Player Name Header with enhanced styling
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.85f, 0.2f, 1.0f));
                ImGui::Text("%s", p.name.c_str());
                ImGui::PopStyleColor();

                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.6f, 0.6f, 0.7f, 1.0f), "  |  %s  |  Age %d",
                    p.position.c_str(), p.age);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Columns(numColumns, nullptr, false);

                // Define stat colors
                ImVec4 labelColor(0.7f, 0.7f, 0.8f, 1.0f);
                ImVec4 valueColor(0.95f, 0.95f, 1.0f, 1.0f);
                ImVec4 highlightColor(0.3f, 0.9f, 0.5f, 1.0f);

                // COLUMN 1 - Team & Shooting
                ImGui::TextColored(labelColor, "Team:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%s", p.team.c_str());

                ImGui::TextColored(labelColor, "Minutes:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%.1f", p.minutes);

                ImGui::TextColored(labelColor, "FG%%:");
                ImGui::SameLine();
                ImGui::TextColored(highlightColor, "%.1f%%", p.FGPercentage);

                ImGui::TextColored(labelColor, "3PT%%:");
                ImGui::SameLine();
                ImGui::TextColored(highlightColor, "%.1f%%", p.ThreePercentage);

                if (numColumns > 1) ImGui::NextColumn();
                else ImGui::Spacing();

                // COLUMN 2 - Scoring & Playmaking
                ImGui::TextColored(labelColor, "Points:");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f), "%.1f", p.points);

                ImGui::TextColored(labelColor, "Assists:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%.1f", p.assists);

                ImGui::TextColored(labelColor, "Rebounds:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%.1f", p.rebounds);

                ImGui::TextColored(labelColor, "Turnovers:");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.9f, 0.4f, 0.4f, 1.0f), "%.1f", p.turnovers);

                if (numColumns > 2) ImGui::NextColumn();
                else if (numColumns > 1) ImGui::Spacing();

                // COLUMN 3 - Defense & Salary
                ImGui::TextColored(labelColor, "Steals:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%.1f", p.steals);

                ImGui::TextColored(labelColor, "Blocks:");
                ImGui::SameLine();
                ImGui::TextColored(valueColor, "%.1f", p.blocks);

                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.4f, 0.9f, 0.4f, 1.0f), "Salary:");
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.5f, 1.0f, 0.5f, 1.0f), "$%.2f", p.salary);

                ImGui::Columns(1);

                ImGui::Spacing();

                ImGui::EndChild();
                ImGui::PopStyleVar(3);
                ImGui::PopStyleColor(2);

                ImGui::Spacing();
                ImGui::Spacing();
            }

            ImGui::EndChild();
        }

        ImGui::End();
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
    }



private:
    std::vector<StatSearchAPI::Player> m_Players;
};

int main(int argc, char* argv[]) {
    StatSearch app;
    app.Run();
}
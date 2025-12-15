#include "Search.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace StatSearchAPI {
    // ----------------------
    // Helper: Convert std::string to lowercase
    // ----------------------
    static std::string toLowerStr(const std::string& s) {
        std::string result = s;
        for (char& c : result) {
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return result;
    }
    // ----------------------
    // Helper: Split CSV line by commas
    // ----------------------
    static std::vector<std::string> splitCSVLine(const std::string& line) {
        std::vector<std::string> cells;
        std::stringstream ss(line);
        std::string cell;
        while (getline(ss, cell, ',')) {
            cells.push_back(cell);
        }
        return cells;
    }

    // ----------------------
    // Search players by partial name, case-insensitive
    // Example: typing "L" finds LeBron James
    // typing "ste" finds Stephen Curry etc.
    // ----------------------
    std::vector<Player> Search::searchByName(std::vector<Player>& players, const std::string& query) {
        std::cout << "Query: " << query << std::endl;
        std::vector<Player> results;
        if (players.empty()) {
            std::cout << "No players loaded.\n";
            return results;
        }
        bool found = false;
        for (auto& p : players) {
            std::string playerNameLower = toLowerStr(p.name);
            std::cout << playerNameLower << std::endl;
            // prefix match (starts with)
            if (playerNameLower.rfind(toLowerStr(query), 0) == 0) {
                p.playerDisplay();
                results.push_back(p);
                std::cout << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No players matched that name.\n";
        }

        return results;
    }
    // ----------------------
    // Filter players by team
    // ----------------------
    void Search::filterByTeam(const std::vector<Player>& players) {
        if (players.empty()) {
            std::cout << "No players loaded.\n";
            return;
        }
        std::string team;
        std::cout << "Enter team abbreviation (LAL, BOS, etc): ";
        std::cin >> team;
        bool found = false;
        for (const auto& p : players) {
            if (p.team == team) {
                p.playerDisplay();
                std::cout << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No players found for that team.\n";
        }
    }
}
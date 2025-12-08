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
    // Load CSV → std::vector<Player>
    // Matches your NBA-players CSV format
    // ----------------------
    std::vector<Player> Search::loadPlayersFromCSV(const std::string& filename) {
        std::vector<Player> players;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Could not open file: " << filename << std::endl;
            return players;
        }
        std::string line;
        getline(file, line); // skip header
        while (getline(file, line)) {
            if (line.empty()) continue;
            std::vector<std::string> cells = splitCSVLine(line);
            if (cells.size() <= 41) continue;
            std::string name = cells[0];
            float salary = stof(cells[1]);
            std::string position = cells[2];
            int age = stoi(cells[3]);
            std::string team = cells[4];
            float minutes = stof(cells[7]);
            float fgPct = stof(cells[10]);
            float threePct = stof(cells[13]);
            float rebounds = stof(cells[23]);
            float assists = stof(cells[24]);
            float steals = stof(cells[25]);
            float blocks = stof(cells[26]);
            float points = stof(cells[29]);
            float turnovers = stof(cells[41]);
            players.emplace_back(
                name, salary, position, age, minutes, team,
                points, rebounds, assists, blocks, steals,
                turnovers, fgPct, threePct
            );
        }
        return players;
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
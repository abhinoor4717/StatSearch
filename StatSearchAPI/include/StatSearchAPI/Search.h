#pragma once

#include <string>
#include <vector>
#include "Player.h"

namespace StatSearchAPI {
    class Search {
    public:
        // Search by exact name match
        static Player searchByName(const std::vector<Player>& players, const std::string& name);
        // Filter players by team
        static void filterByTeam(const std::vector<Player>& players, const std::string& team);
        // TEMP: Load CSV – final version needs correct column order
        static std::vector<Player> loadCSV(const std::string& filename);
    };
}
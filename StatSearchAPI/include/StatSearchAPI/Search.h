#pragma once

#include <string>
#include <vector>
#include "Player.h"

namespace StatSearchAPI {
    class Search {
    public:
        static std::vector<Player> loadPlayersFromCSV(const std::string& filename);
        // Search by name (partial match, case-insensitive)
        static std::vector<Player> searchByName(std::vector<Player>& players, const std::string& query);
        // Filter by team
        static void filterByTeam(const std::vector<Player>& players);
    };
}
#pragma once
#include <string>
#include <vector>
#include <functional>

#include "Player.h"
#include "Search.h"

namespace StatSearchAPI {
	namespace Util {
		std::vector<Player> loadPlayersFromCSV(const std::string& filename);
	}
	namespace Sort {
		using PlayerArg = const Player&;
		using Comparator = std::function<bool(PlayerArg, PlayerArg)>;

		std::vector<Player> sortPlayers(
			std::vector<Player>& players,
			const std::string& playerStat,
			bool ascending = true
		);
	}
}
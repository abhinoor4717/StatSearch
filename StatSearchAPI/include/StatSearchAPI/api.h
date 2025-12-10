#pragma once
#include <string>
#include <vector>

#include "Player.h"
#include "Search.h"

namespace StatSearchAPI {
	namespace Util {
		std::vector<Player> loadPlayersFromCSV(const std::string& filename);
	}
}
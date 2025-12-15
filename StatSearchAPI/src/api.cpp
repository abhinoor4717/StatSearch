#include "api.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace StatSearchAPI {
    namespace Util {
        std::vector<Player> loadPlayersFromCSV(const std::string& filename) {
            std::vector<Player> players;
            std::ifstream file(filename);

            if (!file.is_open()) {
                std::cout << "File could not open";
                return players;
            }

            std::string line;
            int lineNumber = 0;

            while (std::getline(file, line)) {
                lineNumber++;

                std::stringstream ss(line);
                std::vector<std::string> tokens;
                std::string token;

                while (std::getline(ss, token, ',')) {
                    tokens.push_back(token);
                }

                if (tokens.size() >= 14) {
                    try {
                        std::string name = tokens[0];
                        float salary = stof(tokens[1]);
                        std::string position = tokens[2];
                        int age = stoi(tokens[3]);
                        float minutes = stof(tokens[4]);
                        std::string team = tokens[5];
                        float points = stof(tokens[6]);
                        float rebounds = stof(tokens[7]);
                        float assists = stof(tokens[8]);
                        float blocks = stof(tokens[9]);
                        float steals = stof(tokens[10]);
                        float turnovers = stof(tokens[11]);
                        float FGPercentage = stof(tokens[12]);
                        float ThreePercentage = stof(tokens[13]);

                        Player player(name, salary, position, age, minutes, team,
                            points, rebounds, assists, blocks, steals,
                            turnovers, FGPercentage, ThreePercentage);

                        players.push_back(player);
                    }
                    catch (const std::invalid_argument& e) {
                        std::cout << "Error passing line";
                    }
                }


                if (players.empty()) {
                    std::cout << "No players were loaded from the file" << std::endl;
                }

            }

            file.close();
            return players;
        }
    }

    namespace Sort {
        std::string toLowercase(const std::string& input) {
            std::string result = input;
            for (char& character : result) {
                character = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(character))
                    );
            }
            return result;
        }

        // { playerStat (in all lowercase), comparator-lambda }
        const std::unordered_map<std::string, Comparator> comparatorMap = {
          { "age", [](PlayerArg a, PlayerArg b) {
            return a.age < b.age;
          }},
          { "assists", [](PlayerArg a, PlayerArg b) {
            return a.assists < b.assists;
          }},
          { "blocks", [](PlayerArg a, PlayerArg b) {
            return a.blocks < b.blocks;
          }},
          { "fgpercentage", [](PlayerArg a, PlayerArg b) {
            return a.FGPercentage < b.FGPercentage;
          }},
          { "minutes", [](PlayerArg a, PlayerArg b) {
            return a.minutes < b.minutes;
          }},
          { "name", [](PlayerArg a, PlayerArg b) {
                // converting to lowercase so sorting by name is case-insensitve
                // otherwise, a name like "Zane" would come before "asher" because "Z" < "a"
                // * probably unnecessary but i just had to be certain :)
                return toLowercase(a.name) < toLowercase(b.name);
              }},
              { "points", [](PlayerArg a, PlayerArg b) {
                return a.points < b.points;
              }},
              { "position", [](PlayerArg a, PlayerArg b) {
                return toLowercase(a.position) < toLowercase(b.position);
              }},
              { "rebounds", [](PlayerArg a, PlayerArg b) {
                return a.rebounds < b.rebounds;
              }},
              { "salary", [](PlayerArg a, PlayerArg b) {
                return a.salary < b.salary;
              }},
              { "steals", [](PlayerArg a, PlayerArg b) {
                return a.steals < b.steals;
              }},
              { "team", [](PlayerArg a, PlayerArg b) {
                return toLowercase(a.team) < toLowercase(b.team);
              }},
              { "threepercentage", [](PlayerArg a, PlayerArg b) {
                return a.ThreePercentage < b.ThreePercentage;
              }},
              { "turnovers", [](PlayerArg a, PlayerArg b) {
                return a.turnovers < b.turnovers;
              }},
        };

        void bubbleSort(
            std::vector<Player>& players,
            const Comparator& shouldSwap
        ) {
            for (size_t i = 0; i < players.size(); i++) {
                for (size_t j = i + 1; j < players.size(); j++) {
                    if (shouldSwap(players[i], players[j])) {
                        std::swap(players[i], players[j]);
                    }
                }
            }
        }

        std::vector<Player> sortPlayers(
            std::vector<Player>& players,
            const std::string& playerStat,
            bool ascending
        ) {
            std::string normalizedStat = toLowercase(playerStat);

            auto iterator = comparatorMap.find(normalizedStat);
            if (iterator == comparatorMap.end()) {
                // could not find a comparator for stat
                // returns the players vector as is
                return players;
            }

            const Comparator& baseComparator = iterator->second;

            if (ascending) {
                bubbleSort(players, baseComparator);
            }
            else {
                bubbleSort(players, [&baseComparator](PlayerArg a, PlayerArg b) {
                    return baseComparator(b, a); // reverse the baseComparator for descending order
                    });
            }

            return players;
        }

        // overloading - ascending defaults to true if not specified
        std::vector<Player> sortPlayers(
            std::vector<Player>& players,
            const std::string& playerStat
        ) {
            return sortPlayers(players, playerStat, true);
        }
    }
}
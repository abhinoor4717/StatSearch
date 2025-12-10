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
}
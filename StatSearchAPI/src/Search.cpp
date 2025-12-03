#include "Search.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace StatSearchAPI {
     Player Search::searchByName(const std::vector<Player>& players, const std::string& name) {
         bool found = false;
         for (const auto& p : players)
         {
             if (p.name == name)
             {
                 p.playerDisplay();
                 std::cout << "\n";
                 return p;
                 found = true;
             }
         }
         if (!found)
             std::cout << "Player not found.\n";
         }
         // FILTER BY TEAM
         void Search::filterByTeam(const std::vector<Player>& players, const std::string& team)
         {
         bool found = false;
         for (const auto& p : players)
         {
             if (p.team == team)
             {
                 p.playerDisplay();
                 std::cout << "\n";
                 found = true;
             }
         }
         if (!found)
             std::cout << "No players found for this team.\n";
     }
     // CSV LOADER (placeholder — needs correct column order)
     std::vector<Player> Search::loadCSV(const std::string& filename) {
         std::vector<Player> players;
         std::ifstream file(filename);
         if (!file.is_open())
         {
             std::cout << "Could not open file.\n";
             return players;
         }
         std::string line;
         std::getline(file, line); // skip header row for now
         while (std::getline(file, line))
         {
             std::stringstream ss(line);
             std::string name, pos, team;
             float salary, minutes, points, rebounds, assists, blocks, steals, turnovers, fgp, tp;
             int age;
             // PLACEHOLDER — will update once CSV column order is known
             // Example assumes this order:
             // name,salary,position,age,minutes,team,points,rebounds,assists,blocks,steals,turnovers,FG%,3P%
             getline(ss, name, ',');
             ss >> salary; ss.ignore();
             getline(ss, pos, ',');
             ss >> age; ss.ignore();
             ss >> minutes; ss.ignore();
             getline(ss, team, ',');
             ss >> points; ss.ignore();
             ss >> rebounds; ss.ignore();
             ss >> assists; ss.ignore();
             ss >> blocks; ss.ignore();
             ss >> steals; ss.ignore();
             ss >> turnovers; ss.ignore();
             ss >> fgp; ss.ignore();
             ss >> tp; ss.ignore();
             players.emplace_back(
                 name, salary, pos, age, minutes, team,
                 points, rebounds, assists, blocks, steals, turnovers,
                 fgp, tp
             );
         }
         return players;
     }
}
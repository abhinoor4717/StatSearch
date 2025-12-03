#pragma once

#include <string>

namespace StatSearchAPI {
    class Player {
    public:
        std::string name;
        float salary;
        std::string position;
        int age;
        float minutes;
        std::string team;
        float points;
        float rebounds;
        float assists;
        float blocks;
        float steals;
        float turnovers;
        float FGPercentage;
        float ThreePercentage;

        void playerDisplay() const;

        Player(std::string n, float sal, std::string pos, int ag, float m, std::string t, float p, float r, float a, float b, float s, float turn, float fgp, float tp);
    };
}
#include "Player.h"

#include <iostream>

namespace StatSearchAPI {
    Player::Player(std::string n, float sal, std::string pos, int ag, float m, std::string t, float p, float r, float a, float b, float s, float turn, float fgp, float tp) {
        name = n;
        salary = sal;
        position = pos;
        age = ag;
        minutes = m;
        team = t;
        points = p;
        rebounds = r;
        assists = a;
        blocks = b;
        steals = s;
        turnovers = turn;
        FGPercentage = fgp;
        ThreePercentage = tp;
    }

    void Player::playerDisplay() const {
        std::cout << "Name: " << name << ", Age: " << age << ", Team: " << team << ", Position: " << position << ", Salary: " << salary << ", Minutes: " << minutes << ", Points: " << points << ", Rebounds: " << rebounds << ", Assists: " << assists << ", Blocks: " << blocks << ", Steals: " << steals << ", Turnovers: " << turnovers << ", Field Goal Percentage: " << FGPercentage << ", Three Point Percentage: " << ThreePercentage << std::endl;
    }


}
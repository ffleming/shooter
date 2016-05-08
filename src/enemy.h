#pragma once
#include "object.h"
#include <random>
class Enemy : public Object {
    public:
        Enemy() : Object(0.075, 0.0, 0.80, 0.0, 0.0, -0.005, 0.0,
                "data/enemy.vshader", "data/enemy.fshader") {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> randomCoord(-0.9, 0.9);

            this->location.x = randomCoord(gen);
            this->color.red = 0.9;
            this->color.green = 0.0;
            this->color.blue = 0.0;
        };
};

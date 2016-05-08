#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include <random>
class Star : public Object {
    public:
        Star() : Object(0.002, 0.0, 1.0, 0.0, 0.0, -0.025, 0.0, "data/star.vshader", "data/star.fshader") {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> randomCoord(-0.9, 0.9);

            this->location.x = randomCoord(gen);
            this->color.red = 0.9;
            this->color.green = 0.9;
            this->color.blue = 0.9;
        };
};

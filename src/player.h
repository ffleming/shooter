#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <random>
#include "board.h"
#include "object.h"

class PlayerBullet;
class Player : public Object {
    public:
        Player() : Object(0.10, 0, -0.8, 1, 0, 0, 0, "data/player.vshader", "data/player.fshader") {
            randomizeColor();
        };

        friend class Game;
    private:
        std::vector<PlayerBullet> bullets;
        char* vertexShaderPath; //= "data/player.vertexshader";
        char* fragmentShaderPath; //= "data/player.fragmentshader";

};

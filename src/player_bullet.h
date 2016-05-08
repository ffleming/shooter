#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <random>
#include "object.h"
#include "player.h"
#include "star.h"
#include "board.h"

class PlayerBullet : public Object {
    private:
    public:
        friend class Game;
        PlayerBullet(Player* player) : Object::Object(0.0075, player->x(), player->y(),
                player->z(), 0.f, 0.05 + player->yVelocity(), 0.f, "data/player_bullet.vshader", 
                "data/player_bullet.fshader") {
            this->color.red = 1.f;
            this->color.green = 1.f;
            this->color.blue = 0.f;
        }
};

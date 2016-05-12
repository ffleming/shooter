#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <random>
#include <memory>
#include "board.h"
#include "object.h"
#include "player.h"
#include "star.h"
#include "enemy.h"
#include "player_bullet.h"
class Game {
    private:
        bool paused = false;
        bool gameOver = false;
        unsigned int score = 0;
        const int maxStars = 40;
        const int maxEnemies = 15;
        std::shared_ptr<Board> board;
        std::shared_ptr<Player> player;
        std::vector<std::unique_ptr<Star>> stars;
        std::vector<std::shared_ptr<Enemy>> enemies;

        void updateObjects();
        void updateStars();
        void updateEnemies();
        void updatePlayerBullets();
        void updatePlayer();

        void renderObjects(float);
        void renderStars(float);
        void renderPlayerBullets(float);
        void renderEnemies(float);

        void shoot();

        void togglePause();
        void keyDown(int key, int scancode, int mods);
        void keyUp(int key, int scancode, int mods);
        void keyRepeat(int key, int scancode, int mods);
    public:
        Game();
        bool isGameOver() { return this->gameOver; }
        void render(GLFWwindow*);
        void update();
        void processError(int error, const char* description);
        void processKey(GLFWwindow* window, int key, int scancode, int action, int mods);
};

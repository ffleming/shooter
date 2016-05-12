#include "game.h"

/*
 *
 * Collision detection, edge detection, etc occurs in updateFoo() methods
 * Perform collision detection in the update method corresponding to the entitiy that will die
 * Do no enemy/player detection in the bullet methods
 *
 */

Game::Game() {
    board = new Board(2, 2, 0.0);
    player = new Player();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> randomCoord(-0.9, 0.9);
    while(stars.size() <= maxStars) {
        Star newStar;
        newStar.location.x = randomCoord(gen);
        newStar.location.y = randomCoord(gen);
        newStar.location.z = randomCoord(gen);
        stars.push_back(newStar);
    }
}

void Game::update() {
    if(!paused && !gameOver) {
        updateObjects();
    }
}

void Game::updateObjects() {
    updateStars();
    updatePlayerBullets();
    updateEnemies();
    updatePlayer();
    board->update();
}

// TODO: better than n^2 collision detection
void Game::updatePlayer() {
    if((player->velocity.x < 0 && player->edge(Player::Edge::LEFT) > board->leftSurfaceX()) ||
            (player->velocity.x > 0 && player->edge(Player::Edge::RIGHT) < board->rightSurfaceX())) {
        player->location.x += player->velocity.x;
    }
    if((player->velocity.y < 0 && player->edge(Player::Edge::BOTTOM) > board->bottomSurfaceY()) ||
            (player->velocity.y > 0 && player->edge(Player::Edge::TOP) < board->topSurfaceY())) {
        player->location.y += player->velocity.y;
    }

    std::vector<Enemy>::iterator enemy;
    for(enemy = enemies.begin(); enemy < enemies.end(); enemy++) {
        if(player->collidesWith(&*enemy)) {
            std::cout << "I DIED :(\n" << std::flush;
            std::cout << "Score: " << score << "\n" << std::flush;
            gameOver = true;
        }
    }

    player->update();
}

void Game::updateStars() {
    if(stars.size() < maxStars) {
        stars.push_back(Star());
    }
    std::vector<Star>::iterator star;
    for(star = stars.begin(); star < stars.end(); star++) {
        star->location.x += star->velocity.x;
        star->location.y += star->velocity.y;
        star->update();
        if(star->edge(Star::Edge::TOP) < board->bottomSurfaceY()) {
            stars.erase(star);
        }
    }
}

void Game::updatePlayerBullets() {
    std::vector<PlayerBullet>::iterator bullet;
    for(bullet = player->bullets.begin(); bullet < player->bullets.end(); bullet++) {
        bullet->location.x += bullet->velocity.x;
        bullet->location.y += bullet->velocity.y;
        bullet->update();
        if(bullet->edge(PlayerBullet::Edge::BOTTOM) > board->topSurfaceY()) {
            player->bullets.erase(bullet);
        }
    }
}

//TODO: Better collision detection than n^2
void Game::updateEnemies() {
    if(enemies.size() < maxEnemies) {
        enemies.push_back(Enemy());
    }
    std::vector<Enemy>::iterator enemy;
    std::vector<PlayerBullet>::iterator bullet;
    for(enemy = enemies.begin(); enemy < enemies.end(); enemy++) {
        enemy->location.x += enemy->velocity.x;
        enemy->location.y += enemy->velocity.y;
        enemy->update();

        for(bullet = player->bullets.begin(); bullet < player->bullets.end(); bullet++) {
            if(bullet->collidesWith( &*enemy )) {
                enemies.erase(enemy);
                player->bullets.erase(bullet);
                score += 1;
            }
        }

        if(enemy->edge(Enemy::Edge::TOP) < board->bottomSurfaceY()) {
            enemies.erase(enemy);
        }
    }
}

void Game::shoot() {
    player->bullets.push_back(PlayerBullet(player));
}

void Game::render(GLFWwindow* window) {
    float ratio;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;
    glViewport(0, 0, width, height);
    // glClear(GL_COLOR_BUFFER_BIT);
    // glMatrixMode(GL_PROJECTION);
    renderObjects(ratio);
}

void Game::renderObjects(float ratio) {
    board->render(ratio);
    renderStars(ratio);
    renderEnemies(ratio);
    player->render(ratio);
    renderPlayerBullets(ratio);
}

void Game::renderEnemies(float ratio) {
    std::vector<Enemy>::iterator iter;
    for(iter = enemies.begin(); iter < enemies.end(); iter++) {
        iter->render(ratio);
    }

}

void Game::renderStars(float ratio) {
    std::vector<Star>::iterator iter;
    for(iter = stars.begin(); iter < stars.end(); iter++) {
        iter->render(ratio);
    }
}

void Game::renderPlayerBullets(float ratio) {
    std::vector<PlayerBullet>::iterator iter;
    for(iter = player->bullets.begin(); iter < player->bullets.end(); iter++) {
        iter->render(ratio);
    }
}

void Game::togglePause() {
    paused = !paused;
}

void Game::processError(int error, const char* description) {
    fputs(description, stderr);
}

void Game::processKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q) {
        std::cout << "Caught escape, exiting\n" << std::flush;
        gameOver = true;
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    switch(action) {
        case GLFW_PRESS:
            keyDown(key, scancode, mods);
            break;
        case GLFW_REPEAT:
            keyRepeat(key, scancode, mods);
            break;
        case GLFW_RELEASE:
            keyUp(key, scancode, mods);
            break;
    }
}

void Game::keyRepeat(int key, int scancode, int mods) { }
void Game::keyDown(int key, int scancode, int mods) {
    switch(key) {
        case GLFW_KEY_K:
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            player->velocity.y += 0.01;
            break;
        case GLFW_KEY_J:
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            player->velocity.y -= 0.01;
            break;
        case GLFW_KEY_H:
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            player->velocity.x -= 0.01;
            break;
        case GLFW_KEY_L:
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            player->velocity.x += 0.01;
            break;
        case GLFW_KEY_P:
            togglePause();
            break;
        case GLFW_KEY_SPACE:
            shoot();
            break;
         case GLFW_KEY_E:
            enemies.push_back(Enemy());
            break;
        default:
            std::cout << "I don't know what to do with " << key << "!\n" << std::flush;
    }
}

void Game::keyUp(int key, int scancode, int mods) {
    switch(key) {
        case GLFW_KEY_K:
        case GLFW_KEY_W:
        case GLFW_KEY_UP:
            player->velocity.y -= 0.01;
            break;
        case GLFW_KEY_J:
        case GLFW_KEY_S:
        case GLFW_KEY_DOWN:
            player->velocity.y += 0.01;
            break;
        case GLFW_KEY_H:
        case GLFW_KEY_A:
        case GLFW_KEY_LEFT:
            player->velocity.x += 0.01;
            break;
        case GLFW_KEY_L:
        case GLFW_KEY_D:
        case GLFW_KEY_RIGHT:
            player->velocity.x -= 0.01;
            break;
    }
}

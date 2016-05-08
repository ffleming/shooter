#include "board.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

//Height, width etc are all the interior, playable area
Board::Board(float _width, float _height, float _thickness) {
    width = _width;
    height = _height;
    thickness = _thickness;
}

float Board::bottomSurfaceY() {
    // return -height/2;
    return -1.0;
}

float Board::topSurfaceY() {
    // return height/2;
    return 1.0;
}

float Board::leftSurfaceX() {
    // return(-width/2);
    return -1.0;
}

float Board::rightSurfaceX() {
    // return width/2;
    return 1.0;
}

void Board::render(float ratio) {
    /*
    float halfHeight = height/2;
    float halfWidth = width/2;

    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_CULL_FACE);
    glBegin(GL_QUADS);
    glPushMatrix();

    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(halfWidth + thickness, halfHeight, 0.0);
    glVertex3f(halfWidth, halfHeight, 0.0);
    glVertex3f(halfWidth, -halfHeight, 0.0);
    glVertex3f(halfWidth + thickness, -halfHeight, 0.0);

    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-halfWidth, halfHeight, 0.0);
    glVertex3f(-(halfWidth + thickness), halfHeight, 0.0);
    glVertex3f(-(halfWidth + thickness), -halfHeight, 0.0);
    glVertex3f(-halfWidth, -halfHeight, 0.0);

    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex3f(halfWidth + thickness, -halfHeight, 0.0);
    glVertex3f(-(halfWidth + thickness), -halfHeight, 0.0);
    glVertex3f(-(halfWidth + thickness), -(halfHeight + thickness), 0.0);
    glVertex3f(halfWidth + thickness, -(halfHeight + thickness), 0.0);

    glPopMatrix();
    glEnd();
    */
}
void Board::update() {
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
}

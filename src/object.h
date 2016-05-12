#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <random>
#include "board.h"
#include "common/mesh.h"
#include "common/shader.h"
#define OBJECT_VPATH "data/object.vshader"
class Object {
    public:
        friend class Game;
        Object() : Object(0.05, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
                OBJECT_VPATH, "data/object.fshader") {};
        // Object(float sideLength) : Object(sideLength, 0, 1, 0, 0, -.5, 0) {};
        // Object(float sideLength, float x, float y, float z) : Object(sideLength, x, y, z, 0, 0, 0) {};
        Object(float sideLength, float x, float y, float z, float xVel, float yVel, float zVel,
                const char* vertexPath, const char* fragmentPath);
        ~Object();
        virtual void render(float);
        void update();
        enum class Direction { UP, DOWN, LEFT, RIGHT};
        enum class Edge { TOP, BOTTOM, LEFT, RIGHT};
        float x();
        float y();
        float z();
        float xVelocity();
        float yVelocity();
        float zVelocity();
        // Mesh* mesh;

    protected:
        GLuint loadShader(const char*, const char*);
        GLuint programId = -1;
        GLuint vao;
        GLuint vbo;

        bool collidesWith(std::shared_ptr<Object> obj);
        float edge(Edge);
        struct color {
            float red;
            float green;
            float blue;
        } color;
        typedef struct {
            float x;
            float y;
            float z;
        } triple;
        triple location;
        triple velocity;
        void x(float);
        void y(float);
        void z(float);
        void xVelocity(float);
        void yVelocity(float);
        void zVelocity(float);

        void randomizeColor();
        float height;
        float width;
        float depth;

    private:
};

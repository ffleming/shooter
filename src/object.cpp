#include "object.h"

Object::Object(float sideLength, float x, float y, float z, float xVel, float yVel, float zVel,
        const char* vertexPath, const char* fragmentPath) {
    height = sideLength;
    width = sideLength;
    depth = 1;

    location.x = x;
    location.y = y;
    location.z = z;
    velocity.x = xVel;
    velocity.y = yVel;
    velocity.z = zVel;

    color.red = 1;
    color.green = 1;
    color.blue = 1;
    programId = LoadShaders(vertexPath, fragmentPath);
    glGenBuffers(1, &vbo);
}

/*
 * TODO: lol there is no need to have a different programId for each object, this is insane
 
GLuint Object::loadShader(const char* vertexPath, const char* fragmentPath) {
    std::cout << programId << "\n" << std::flush;
    // if(programId != -1) {
    //     return programId;
    // }
    std::cout << programId << "\n" << std::flush;
    return 
}
*/

float Object::x() {
    return location.x;
}

float Object::y() {
    return location.y;
}

float Object::z() {
    return location.z;
}

float Object::xVelocity() {
    return velocity.x;
}

float Object::yVelocity() {
    return velocity.y;
}

float Object::zVelocity() {
    return velocity.z;
}

void Object::x(float input) {
    location.x = input;
}

void Object::y(float input) {
    location.y = input;
}

void Object::z(float input) {
    location.z = input;
}

void Object::xVelocity(float input) {
    velocity.x = input;
}

void Object::yVelocity(float input) {
    velocity.y = input;
}

void Object::zVelocity(float input) {
    velocity.z = input;
}

bool Object::collidesWith(Object* other) {
    if(this->edge(Object::Edge::LEFT) > other->edge(Object::Edge::RIGHT)) {
        return false;
    }
    if(this->edge(Object::Edge::RIGHT) < other->edge(Object::Edge::LEFT)) {
        return false;
    }
    if(this->edge(Object::Edge::BOTTOM) > other->edge(Object::Edge::TOP)) {
        return false;
    }
    if(this->edge(Object::Edge::TOP) < other->edge(Object::Edge::BOTTOM)) {
        return false;
    }
    return true;
}

// TODO: Don't create a new randomizer for every call. Need to make static while keeping instance
// access to the color typedef
void Object::randomizeColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> randomColor(0, 1);

    color.red = randomColor(gen);
    color.green = randomColor(gen);
    color.blue = randomColor(gen);
}

float Object::edge(Edge e) {
    switch(e) {
        case Edge::TOP:
            return(location.y + height/2);
            break;
        case Edge::BOTTOM:
            return(location.y - height/2);
            break;
        case Edge::LEFT:
            return(location.x - width/2);
            break;
        case Edge::RIGHT:
            return(location.x + width/2);
            break;
    }
}

void Object::render(float ratio) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    GLfloat vertices[18] = {
        // bottom right corner
        location.x + width / 2, location.y - height/2, depth,
        // top right corner
        location.x + width / 2, location.y + height/2, depth,
        // top left corner
        location.x - width / 2, location.y + height/2, depth,
        // top left corner
        location.x - width / 2, location.y + height/2, depth,
        // bottom left corner
        location.x - width / 2, location.y - height/2, depth,
        // bottom right corner
        location.x + width / 2, location.y - height/2, depth,
    };
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glUseProgram(programId);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(
            glGetAttribLocation(programId,"Position"),
            3,           // size
            GL_FLOAT,
            GL_FALSE,    // normalized?
            0,           // stride
            (void*)0     // array buffer offset
            );

    glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

    // glDisableVertexAttribArray(0);
}

Object::~Object() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
    // Don't do this - it looks like OpenGL is smart enough to reuse the same shader instead
    // of making new ones ?
	// glDeleteProgram(programId);
}

void Object::update() {
}

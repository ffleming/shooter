#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "game.h"
#include "object.h"
#include "common/mesh.h"

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

GLFWwindow* window;
Game* game;

bool initialize_graphics ( void ) {
	// Initialise GLFW
	if( !glfwInit() ) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 768, 768, "Dogs are cool", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window.\n" );
		getchar();
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return false;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);

    return true;
}

bool game_loop( void) {
    game->update();
    game->render(window);
    return true;
}

int main( void ) {
    initialize_graphics();
    game = new Game();
    Object* o = new Object();

	// while( glfwWindowShouldClose(window) == 0 ) {
	while(game->isGameOver() == false) {
		glClear( GL_COLOR_BUFFER_BIT );
        game_loop();
		glfwSwapBuffers(window);
		glfwPollEvents();
    }

	glfwTerminate();

	return 0;
}




void error_callback(int error, const char* description) {
    game->processError(error, description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    game->processKey(window, key, scancode, action, mods);
}


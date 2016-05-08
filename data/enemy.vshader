#version 410 core

// Input vertex data, different for all executions of this shader.
in vec3 Position;

void main(){

    gl_Position.xyz = Position;
    gl_Position.w = 1.0;

}


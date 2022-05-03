#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "io.h"

#define VERT_SIZE   3
#define PI          3.14159

SDL_Window* createWindow(int width, int height);

void clearScreen();

GLuint compileShader(const char* path, GLenum type);
GLuint compileShaderProgram(const char* vsPath, const char* fsPath);

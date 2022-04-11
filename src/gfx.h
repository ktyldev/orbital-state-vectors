#pragma once

#define GLEW_STATIC
#include "GL/glew.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "io.h"

SDL_Window* createWindow(int width, int height);

GLuint compileShader(const char* path, GLenum type);
GLuint compileShaderProgram(const char* vsPath, const char* fsPath);

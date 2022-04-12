#include "main.h"

SDL_Window *window;
GLuint vao;
GLuint vbo;
GLuint shaderProgram;

const int WIDTH = 420;
const int HEIGHT = 420;

void init() 
{ 
    window = createWindow(WIDTH, HEIGHT);

    // create shader program
    shaderProgram = compileShaderProgram("bin/vert.glsl", "bin/frag.glsl");
    glUseProgram(shaderProgram);
}

int main()
{
    printf("hello, world! welcome home :)\n");

    init();

    // TODO: vertices for trajectory
    // TODO: 3D camera

    // generate a grid
    struct Grid grid;
    int n = 6;
    generateGrid(&grid, n);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
        // TODO: clear screen

        drawGrid(grid, shaderProgram);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

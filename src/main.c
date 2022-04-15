#include "main.h"

SDL_Window *window;
GLuint vao;
GLuint vbo;
GLuint shaderProgram;

const int WIDTH = 900;
const int HEIGHT = 900;

void init() 
{ 
    window = createWindow(WIDTH, HEIGHT);

    // create shader program
    shaderProgram = compileShaderProgram("bin/vert.glsl", "bin/frag.glsl");
    glUseProgram(shaderProgram);
}

void clearScreen()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main()
{
    init();

    printf("hello, world! welcome home :)\n");
    printf("%d\n", signbit(-5.0));

    // 3D camera with view and projection matrices
    struct Camera camera;
    createCamera(&camera);

    // generate scene objects
    struct Grid grid;
    struct Trajectory trajectory;
    generateGrid(&grid, 20);
    generateTrajectory(&trajectory, 100);

    mat4 model;
    glm_mat4_identity(model);

    // upload matrices to shader uniforms
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, (float*)model);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
        clearScreen();

        updateCamera(&camera, shaderProgram);

        drawGrid(grid, shaderProgram);
        drawTrajectory(trajectory, shaderProgram);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

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
    init();

    printf("hello, world! welcome home :)\n");

    // generate scene objects
    struct Grid grid;
    struct Trajectory trajectory;
    generateGrid(&grid, 6);
    generateTrajectory(&trajectory, 100);

    // 3D camera with view and projection matrices
    struct Camera camera = createCamera();

    // TODO: the model matrix will be updated at runtime later in order for 
    // the model to spin.
    mat4 model;
    glm_mat4_identity(model);

    // upload matrices to shader uniforms
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    GLint uniProjection = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(uniModel, 1, GL_FALSE, (float*)model);
    glUniformMatrix4fv(uniView, 1, GL_FALSE, (float*)camera.view);
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, (float*)camera.proj);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
        // TODO: clear screen

        drawGrid(grid, shaderProgram);
        drawTrajectory(trajectory, shaderProgram);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

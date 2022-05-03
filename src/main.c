#include "main.h"

SDL_Window *window;
GLuint vao;
GLuint vbo;
GLuint shaderProgram;

const int WIDTH = 900;
const int HEIGHT = 900;

struct Scene scene;

void openWindow()
{ 
    window = createWindow(WIDTH, HEIGHT);

    // create shader program
    shaderProgram = compileShaderProgram("bin/vert.glsl", "bin/frag.glsl");
    glUseProgram(shaderProgram);
}

int main()
{
    openWindow();
    createScene(&scene);

    mat4 model;
    glm_mat4_identity(model);

    // upload matrices to shader uniforms
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, (float*)model);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
        // update
        updateCamera(&scene.camera, shaderProgram);

        // render
        clearScreen();

        // draw stuff
        drawGrid(scene.grid, shaderProgram);
        drawTrajectory(scene.trajectory, shaderProgram);
        drawCircle(scene.origin, shaderProgram);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}

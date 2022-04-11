#include "main.h"

SDL_Window *window;
GLuint vao;
GLuint vbo;

const int WIDTH = 420;
const int HEIGHT = 420;

void init() 
{ 
    window = createWindow(WIDTH, HEIGHT);
}

int main()
{
    printf("hello, world! welcome home :)\n");

    init();

    // create vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create vertex buffer object
    GLfloat vertexPositions[2*2] = 
    {
        -0.5, -0.5, 
         0.5,  0.5
    };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // create shader program
    GLuint shaderProgram = compileShaderProgram("bin/vert.glsl", "bin/frag.glsl");
    glUseProgram(shaderProgram);

    // vertex positions
    GLint pos = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos);

    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2);
    SDL_GL_SwapWindow(window);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
    }

    return 0;
}

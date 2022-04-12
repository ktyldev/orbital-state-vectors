#include "main.h"

SDL_Window *window;
GLuint vao;
GLuint vbo;
GLuint shaderProgram;

const int WIDTH = 420;
const int HEIGHT = 420;
const int VERT_SIZE = 2;

struct Grid
{
    GLfloat* vertices;
    int vertCount;
    GLuint vbo;
    GLuint vao;
};

// generate a grid with side length n. n refers to the vertices per side, not tiles.
//
// generate static data to do with the grid, so all the vertex data, vertex attributes, vbo and vao.
// none of this data should change while the application is running.
//
//          0 2 4
//      
//      6   x x x   7
//      8   x x x   9
//      10  x x x   11
//
//          1 3 5
//
// Grid*        g   generated grid data stored in a struct
// dimension    n   side length of a square grid i.e 1->1 points, 2->4 points, 3->9 ...
void generateGrid(struct Grid* g, int n)
{
    // allocate space for vertices
    g->vertices = calloc(4 * n * VERT_SIZE, sizeof(GLfloat));

    for (int i = 0; i < n; i++)
    {
        // base vertex index for column
        int vi = 2 * VERT_SIZE * i;

        float x = i;
        float y = 0;

        g->vertices[vi + 0] = x;
        g->vertices[vi + 1] = y;
        g->vertices[vi + 2] = x;
        g->vertices[vi + 3] = n-1;
    }

    for (int i = 0; i < n; i++)
    {
        int vi = 2 * VERT_SIZE * (i + n);

        float x = i;
        float y = 0;

        g->vertices[vi + 1] = x;
        g->vertices[vi + 0] = y;
        g->vertices[vi + 3] = x;
        g->vertices[vi + 2] = n-1;
    }

    float scale = 1.0/(float)(n-1);
    float offset = -0.5;
    for (int i = 0; i < 4 * VERT_SIZE * n; i++)
    {
        g->vertices[i] *= scale;
        g->vertices[i] += offset;
    }

    glGenVertexArrays(1, &(*g).vao);
    glBindVertexArray(g->vao);

    g->vertCount = 4*n;
}

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

    int vboLength = 4*n*2*VERT_SIZE;

    // generate a vertex buffer
    glGenBuffers(1, &vbo);

    // bind the vbo...
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // .. and upload vertex data to the bound vbo.
    glBufferData(GL_ARRAY_BUFFER, vboLength*sizeof(GLfloat), grid.vertices, GL_STATIC_DRAW);

    // vertex positions
    GLint pos = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(pos, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos);

    glBindVertexArray(grid.vao);
    glDrawArrays(GL_LINES, 0, grid.vertCount);
    SDL_GL_SwapWindow(window);

    int frames;
    for (frames = 0; !checkQuit(); frames++)
    {
        // draw grid
    }

    return 0;
}

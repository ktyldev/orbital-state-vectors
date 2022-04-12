#include "grid.h"

// populate just the vertex data for the grid
void generateGridVertices(struct Grid* g, int n)
{
    // allocate space for vertices
    g->vertices = calloc(4 * n * VERT_SIZE, sizeof(GLfloat));

    // generate columns
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

    // generate rows
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

    // scale and position the grid to fit centrally in the window
    float scale = 1.0/(float)(n-1);
    float offset = -0.5;
    for (int i = 0; i < 4 * VERT_SIZE * n; i++)
    {
        g->vertices[i] *= scale;
        g->vertices[i] += offset;
    }
}

void generateGrid(struct Grid* g, int n)
{
    generateGridVertices(g, n);

    glGenVertexArrays(1, &(*g).vao);
    glBindVertexArray(g->vao);

    g->vertCount = 4*n;

    g->vboLength = 4*n*VERT_SIZE;

    // generate a vertex buffer
    glGenBuffers(1, &(*g).vbo);

    // bind the vbo...
    glBindBuffer(GL_ARRAY_BUFFER, g->vbo);
    // ...and upload vertex data to the bound vbo.
    // we use GL_STATIC_DRAW for the usage pattern because we do not expect grid vertices to change
    // while the application is running.
    glBufferData(GL_ARRAY_BUFFER, g->vboLength*sizeof(GLfloat), g->vertices, GL_STATIC_DRAW);
}

void drawGrid(struct Grid g, GLuint shaderProgram)
{
    // enable vertex attribute arrays for grid
    GLint pos = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(pos, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos);

    // draw grid
    glBindVertexArray(g.vao);
    glDrawArrays(GL_LINES, 0, g.vertCount);
}

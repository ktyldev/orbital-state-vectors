#include "grid.h"

// populate just the vertex data for the grid
void generateGridVertices(struct Grid* g, int n)
{
    // allocate space for vertices
    g->vertices = calloc(4 * n * VERT_SIZE, sizeof(GLfloat));

    float offset = -0.5;

    // generate columns
    for (int i = 0; i < n; i++)
    {
        // base vertex index for column
        int vi = 2 * VERT_SIZE * i;

        float x = i;
        float y = 0;
        float z = 0;

        g->vertices[vi + 0] = x;
        g->vertices[vi + 1] = y;
        g->vertices[vi + 2] = z;
        g->vertices[vi + 3] = x;
        g->vertices[vi + 4] = n-1;
        g->vertices[vi + 5] = z;
    }

    // generate rows
    for (int i = 0; i < n; i++)
    {
        int vi = 2 * VERT_SIZE * (i + n);

        float x = 0;
        float y = i;
        float z = 0;

        g->vertices[vi + 0] = x;
        g->vertices[vi + 1] = y;
        g->vertices[vi + 2] = z;
        g->vertices[vi + 3] = n-1;
        g->vertices[vi + 4] = y;
        g->vertices[vi + 5] = z;
    }

    // scale and position the grid to fit centrally in the window
    float scale = 1.0/(float)(n-1);
    for (int i = 0; i < 4 * VERT_SIZE * n; i++)
    {
        g->vertices[i] *= scale;

        if (i % 3 != 2)
        {
            g->vertices[i] += offset;
        }
    }
}

void generateGrid(struct Grid* g, int n)
{
    g->vertCount = 4*n;
    int vboLength = g->vertCount*VERT_SIZE;

    generateGridVertices(g, n);

    glGenVertexArrays(1, &(*g).vao);
    glBindVertexArray(g->vao);

    // generate a vertex buffer
    glGenBuffers(1, &(*g).vbo);

    // bind the vbo...
    glBindBuffer(GL_ARRAY_BUFFER, g->vbo);
    // ...and upload vertex data to the bound vbo.
    // we use GL_STATIC_DRAW for the usage pattern because we do not expect grid vertices to change
    // while the application is running.
    glBufferData(GL_ARRAY_BUFFER, vboLength*sizeof(GLfloat), g->vertices, GL_STATIC_DRAW);
}

void drawGrid(struct Grid g, GLuint shaderProgram)
{
    GLint pos = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(pos, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos);

    glBindBuffer(GL_ARRAY_BUFFER, g.vbo);

    // draw grid
    glBindVertexArray(g.vao);
    glDrawArrays(GL_LINES, 0, g.vertCount);
}

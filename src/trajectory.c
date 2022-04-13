#include "trajectory.h"

// TODO: look up more digits of pi
#define PI 3.14159

void generateTrajectory(struct Trajectory* t, int n)
{
    t->vertCount = n;
    t->vertices = calloc(n * VERT_SIZE, sizeof(GLfloat));

    for (int i = 0; i < n; i++)
    {
        int vi = VERT_SIZE * i;

        float a = (float)i / (float)n * 2 * PI;
        float x = cos(a);
        float y = sin(a);

        t->vertices[vi + 0] = x;
        t->vertices[vi + 1] = y;
    }

    for (int i = 0; i < 2 * n; i++)
    {
        t->vertices[i] *= 0.5;
    }

    glGenVertexArrays(1, &(t->vao));
    glBindVertexArray(t->vao);

    glGenBuffers(1, &(t->vbo));

    glBindBuffer(GL_ARRAY_BUFFER, t->vbo);
    glBufferData(GL_ARRAY_BUFFER, n*VERT_SIZE*sizeof(GLfloat), t->vertices, GL_STATIC_DRAW);
}

void drawTrajectory(struct Trajectory t, GLuint shaderProgram)
{
    GLint pos = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(pos, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(pos);

    glBindBuffer(GL_ARRAY_BUFFER, t.vbo);

    glBindVertexArray(t.vao);
    glDrawArrays(GL_LINE_LOOP, 0, t.vertCount);
}

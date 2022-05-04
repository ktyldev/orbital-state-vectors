#include "circle.h"

const int EDGES = 100;

void generateCircle(struct Circle* c, float r)
{
    c->vertCount = EDGES + 2;
    c->vertices = calloc(c->vertCount * VERT_SIZE, sizeof(GLfloat));

    // assign the first vertex in the middle
    c->vertices[0] = 0;
    c->vertices[1] = 0;
    c->vertices[2] = 0;

    // add more vertices in a circle around the first one
    for (int i = 0; i <= EDGES; i++)
    {
        float a = (float)i / (float)EDGES * 2 * PI;

        // calculate x, y, z coordinates of circle
        float x = sin(a) * r;
        float y = cos(a) * r;
        float z = 0;

        int vi = VERT_SIZE * (i + 1);
        c->vertices[vi + 0] = x;
        c->vertices[vi + 1] = y;
        c->vertices[vi + 2] = z;
    }

    glm_vec3_copy(GLM_VEC3_ZERO, c->pos);

    glGenVertexArrays(1, &(c->vao));
    glBindVertexArray(c->vao);

    glGenBuffers(1, &(c->vbo));

    glBindBuffer(GL_ARRAY_BUFFER, c->vbo);
    glBufferData(GL_ARRAY_BUFFER, c->vertCount * VERT_SIZE * sizeof(GLfloat), c->vertices, GL_STATIC_DRAW);
}

void drawCircle(struct Circle c, GLuint shaderProgram)
{
    // first we want to draw a circle of points around the origin
    GLint loc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(loc, 1.0, 0.7, 0.5);

    loc = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(loc, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, c.vbo);

    glBindVertexArray(c.vao);

    // always face the camera
    vec3 camPos;
    getCameraPos(camPos);

    mat4 lookat;
    mat4 model;
    glm_lookat(c.pos, camPos, GLM_YUP, lookat);
    glm_mat4_inv(lookat, model);

    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, (float*)model);

    glDrawArrays(GL_TRIANGLE_FAN, 0, c.vertCount);
}

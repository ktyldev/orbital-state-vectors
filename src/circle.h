#pragma once

#include "gfx.h"

struct Circle
{
    GLfloat* vertices;
    GLuint vbo;
    GLuint vao;
    float radius;
    int vertCount;
};

// generate a circle in the XZ world space plane with radius r.
void generateCircle(struct Circle* c, float r);
void drawCircle(struct Circle c, GLuint shaderProgram);

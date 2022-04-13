#pragma once

#include "gfx.h"

struct Trajectory
{
    GLfloat* vertices;
    int vertCount;
    GLuint vbo;
    GLuint vao;
};

// generate a circular trajectory around the origin using n vertices.
void generateTrajectory(struct Trajectory* t, int n);
void drawTrajectory(struct Trajectory t, GLuint shaderProgram);

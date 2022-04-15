#pragma once

#include <math.h>
#include <cglm/vec3.h>

#include "ellipse.h"
#include "gfx.h"

#define PI 3.14159

struct Trajectory
{
    GLfloat* vertices;
    int vertCount;
    GLuint vbo;
    GLuint vao;
};

// generate a trajectory around the origin using n vertices.
void generateTrajectory(struct Trajectory* t, int n);
void drawTrajectory(struct Trajectory t, GLuint shaderProgram);

void transformPoint(vec2 p2, vec3 p3);

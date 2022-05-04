#pragma once

#include "gfx.h"
// we need to include the camera to determine its position. alternatively, would it be better
// to pass it in as a parameter?
#include "cam.h"

struct Circle
{
    GLfloat* vertices;
    GLuint vbo;
    GLuint vao;
    float radius;
    int vertCount;
    vec3 pos;
};

// generate a circle in the XZ world space plane with radius r.
void generateCircle(struct Circle* c, float r);
void drawCircle(struct Circle c, GLuint shaderProgram);

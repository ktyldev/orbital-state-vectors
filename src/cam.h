#pragma once

#include "gfx.h"
#include "clock.h"

#include <cglm/cam.h>

#define ASPECT  1   // TODO: actually get this from screen dims
#define NEAR    0.01
#define FAR     1000

struct Camera
{
    vec3 pos;
    vec3 up;
    mat4 view;
    mat4 proj;
    float fov;
};
void createCamera(struct Camera* c);
void updateCamera(struct Camera* c, GLuint shaderProgram);

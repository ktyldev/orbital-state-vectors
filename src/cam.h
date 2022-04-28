#pragma once

#include "gfx.h"
#include "clock.h"

#include <cglm/cam.h>

#define ASPECT  1   // TODO: actually get this from screen dims
#define NEAR    0.01
#define FAR     1000

#define CAM_SPEED               0.5
#define CAM_DISTANCE            2.0
#define CAM_HEIGHT              0.6
#define CAM_HEIGHT_VARIANCE     0.1

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

void getCameraPos(vec3 pos);

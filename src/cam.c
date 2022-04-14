#include "cam.h"

void createCamera(struct Camera* c)
{
    c->fov = 40;

    vec3 pos = {0.5,1.5,2.0};
    glm_vec3_copy(pos, c->pos);

    vec3 up = {0.0,1.0,0.0};
    glm_vec3_copy(up, c->up);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);
    glm_perspective(glm_rad(c->fov), ASPECT, NEAR, FAR, c->proj);

    return c;
}

void updateCamera(struct Camera* c)
{
    float d = 2.0;              // distance
    float h = 1.5;              // height
    float speed = 1.0;
    float t = now() * speed;

    float x = sin(t) * d;
    float z = cos(t) * d;

    vec3 pos = {x,h,z};
    glm_vec3_copy(pos, c->pos);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);
}

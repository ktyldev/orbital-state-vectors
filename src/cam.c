#include "cam.h"

void createCamera(struct Camera* c)
{
    c->fov = 30;

    vec3 up = {0.0,1.0,0.0};
    glm_vec3_copy(up, c->up);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);
    glm_perspective(glm_rad(c->fov), ASPECT, NEAR, FAR, c->proj);
}

void updateCamera(struct Camera* c, GLuint shaderProgram)
{
    float d = 2.0;              // distance
    float h = 1.0;              // height
    float speed = 0.5;
    float t = now() * speed;

    float x = sin(t) * d;
    float z = cos(t) * d;

    vec3 pos = {x,h,z};
    glm_vec3_copy(pos, c->pos);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);

    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    GLint uniProjection = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(uniView, 1, GL_FALSE, (float*)c->view);
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, (float*)c->proj);
}

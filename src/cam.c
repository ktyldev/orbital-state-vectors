#include "cam.h"

void createCamera(struct Camera* c)
{
    c->fov = 60;

    vec3 up = {0.0,1.0,0.0};
    glm_vec3_copy(up, c->up);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);
    glm_perspective(glm_rad(c->fov), ASPECT, NEAR, FAR, c->proj);
}

void updateCamera(struct Camera* c, GLuint shaderProgram)
{
    float d = 2.0;              // distance
    float h = 0.6;              // height
    float hv = 0.1;             // height variance
    float speed = 0.5;
    float t = now() * speed;

    float x = sin(t) * d;
    float y = cos(t * 0.5) * hv + h;
    float z = cos(t) * d;

    vec3 pos = {x,y,z};
    glm_vec3_copy(pos, c->pos);

    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);

    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    GLint uniProjection = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(uniView, 1, GL_FALSE, (float*)c->view);
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, (float*)c->proj);
}

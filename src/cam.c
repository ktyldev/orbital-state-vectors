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
    getCameraPos(c->pos);
    glm_lookat(c->pos, GLM_VEC3_ZERO, c->up, c->view);

    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    GLint uniProjection = glGetUniformLocation(shaderProgram, "projection");

    glUniformMatrix4fv(uniView, 1, GL_FALSE, (float*)c->view);
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, (float*)c->proj);
}

void getCameraPos(vec3 pos)
{
    float d = CAM_DISTANCE;
    float hv = CAM_HEIGHT_VARIANCE;
    float h = CAM_HEIGHT;
    float t = now() * CAM_SPEED;

    pos[0] = sin(t) * d;
    pos[1] = cos(t * 0.5) * hv + h;
    pos[2] = cos(t) * d;
}

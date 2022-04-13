#include "cam.h"

struct Camera createCamera()
{
    struct Camera c;

    const int fovy = 40;

    vec3 pos = {0.5,1.5,2.0};
    vec3 up = {0.0,1.0,0.0};

    glm_vec3_copy(pos, c.pos);
    glm_vec3_copy(up, c.up);
    glm_lookat(c.pos, GLM_VEC3_ZERO, c.up, c.view);
    glm_perspective(glm_rad(fovy), ASPECT, NEAR, FAR, c.proj);

    return c;
}

#include "trajectory.h"

void generateTrajectory(struct Trajectory* t, int n)
{
    t->vertCount = n;
    t->vertices = calloc(n * VERT_SIZE, sizeof(GLfloat));

    struct Ellipse e;
    e.a = 1.0;
    e.e = 0.5;

    for (int i = 0; i < n; i++)
    {
        int vi = VERT_SIZE * i;

        float a = (float)i / (float)n * 2 * PI;

        // position on ellipse
        vec2 e_pos;
        getPosition(e, a, e_pos);

        // ellipse position transformed with respect to the orbit and its focus
        vec3 o_pos;
        transformPoint(e, e_pos, o_pos);

        float x = o_pos[0];
        float y = o_pos[1];
        float z = o_pos[2];

        t->vertices[vi + 0] = x;
        t->vertices[vi + 1] = y;
        t->vertices[vi + 2] = z;
    }

    for (int i = 0; i < VERT_SIZE * n; i++)
    {
        t->vertices[i] *= 0.5;
    }

    glGenVertexArrays(1, &(t->vao));
    glBindVertexArray(t->vao);

    glGenBuffers(1, &(t->vbo));

    glBindBuffer(GL_ARRAY_BUFFER, t->vbo);
    glBufferData(GL_ARRAY_BUFFER, n*VERT_SIZE*sizeof(GLfloat), t->vertices, GL_STATIC_DRAW);
}

void drawTrajectory(struct Trajectory t, GLuint shaderProgram)
{
    // upload uniforms
    mat4 model;
    glm_mat4_identity(model);
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, (float*)model);
    GLint loc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(loc, 0.9, 0.9, 1.0);

    // set vertex attributes
    loc = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(loc, VERT_SIZE, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc);

    glBindBuffer(GL_ARRAY_BUFFER, t.vbo);

    glBindVertexArray(t.vao);
    glDrawArrays(GL_LINE_LOOP, 0, t.vertCount);
}

void transformPoint(struct Ellipse e, vec2 p2, vec3 p3)
{
    // distance from the origin to the focus of the trajectory
    double focusDistance = getFocusDistance(e);

    double x = p2[0] + focusDistance;
    double z = p2[1];

    vec3 up = {0.0,1.0,0.0};

    p3[0] = x;
    p3[1] = 0;
    p3[2] = z;

    double p = glm_rad(45.0);       // argument of periapsis
    double W = glm_rad(17.0);       // argument of ascending node
    double i = glm_rad(20.0);       // inclination

    vec3 toW = {cos(W), 0, sin(W)}; // vector from origin to ascending node

    glm_vec3_rotate(p3, p, up);     // rotate by argument of periapsis
    glm_vec3_rotate(p3, W, up);     // rotate by argument of ascending node
    glm_vec3_rotate(p3, i, toW);    // rotate by inclination
}


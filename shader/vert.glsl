#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;

out vec3 vpos;

void main()
{
    vec3 p = position;
    mat4 camera = projection * view;

    gl_Position = camera * model * vec4(p, 1.0);

    vpos = p;
}

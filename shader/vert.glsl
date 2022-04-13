#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec3 position;

void main()
{
    mat4 camera = projection * view;

    gl_Position = camera * model * vec4(position, 1.0);
}

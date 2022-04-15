#version 150

uniform vec3 color;

in vec3 vpos;

out vec4 outColor;

void main()
{
    float max = 2.0;
    float r = smoothstep(1, 0, length(vpos) / max);

    outColor = vec4(color, 1.0) * r;
}

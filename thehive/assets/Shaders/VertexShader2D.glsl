#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;
layout(location = 2) uniform float alpha;
layout(location = 3) uniform float Zindex;

out vec2 Texcoord;
out float Alpha;

void main() {
    Texcoord = texcoord;
    Alpha    = alpha;

    gl_Position = vec4(position, Zindex, 1.0);
};

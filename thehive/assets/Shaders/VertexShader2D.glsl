#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;
layout(location = 3) uniform float Zindex;

out vec2 Texcoord;

void main() {
    Texcoord=texcoord;
    gl_Position = vec4(position,Zindex, 1.0);
};

#version 400

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;
uniform float Zindex;

out vec2 Texcoord;

void main() {
    Texcoord=texcoord;
    gl_Position = vec4(position,Zindex, 1.0);
};

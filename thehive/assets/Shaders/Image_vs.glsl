#version 450

layout(location = 0) in vec2 VertexPosition;
layout(location = 1) in vec2 VertexUV;

layout(location = 3) uniform float Zindex;

out vec2 UV;

void main() {
    UV = VertexUV;

    gl_Position = vec4(VertexPosition, Zindex, 1.0);
};

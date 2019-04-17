#version 400

layout(location = 0) in vec2 position;
uniform float Zindex;

void main() {
    gl_Position = vec4(position,Zindex, 1.0);
};

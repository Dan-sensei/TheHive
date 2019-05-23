#version 450

layout(location = 2) uniform vec3 inputColour;
layout(location = 3) uniform float Alpha;

out vec4 frag_colour;

void main() {
    frag_colour = vec4(inputColour, Alpha);
};

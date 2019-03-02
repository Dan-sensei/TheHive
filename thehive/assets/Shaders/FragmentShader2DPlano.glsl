#version 400

uniform vec4 inputColour;

out vec4 frag_colour;

void main() {
    frag_colour = inputColour;
};

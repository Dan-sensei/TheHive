#version 400

uniform sampler2D DiffuseMap;
uniform vec4 inputColour;

in vec2 Texcoord;

out vec4 frag_colour;

void main() {
    frag_colour = texture(DiffuseMap, Texcoord)*inputColour;

};

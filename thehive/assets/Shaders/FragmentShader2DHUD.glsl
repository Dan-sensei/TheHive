#version 450

layout(binding = 0) uniform sampler2D DiffuseMap;

in vec2 Texcoord;
in float Alpha;

out vec4 frag_colour;

void main() {
    frag_colour = texture(DiffuseMap, Texcoord)*Alpha;
};

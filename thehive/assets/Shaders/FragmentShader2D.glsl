#version 450

layout(binding = 0) uniform sampler2D DiffuseMap;
layout(location = 4) uniform vec4 inputColour;

in vec2 Texcoord;

out vec4 frag_colour;

void main() {
    vec4 color = texture(DiffuseMap, Texcoord)*inputColour;
    if(color.a<0.9){
        discard;
    }
    frag_colour = color;

};

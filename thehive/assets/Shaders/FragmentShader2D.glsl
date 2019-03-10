#version 400

uniform sampler2D DiffuseMap;
uniform vec4 inputColour;

in vec2 Texcoord;

out vec4 frag_colour;

void main() {
    vec4 color = texture(DiffuseMap, Texcoord)*inputColour;
    if(color.a<0.1){
        discard;
    }
    frag_colour = color;

};

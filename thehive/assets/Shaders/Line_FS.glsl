#version 400

out vec4 frag_colour;

uniform vec3 Color;

void main() {


  frag_colour = vec4(Color, 1);

};

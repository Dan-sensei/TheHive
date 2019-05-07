#version 450

out vec4 frag_colour;

layout(location = 2) uniform vec3 Color;

void main() {


  frag_colour = vec4(Color/255.f, 1);

};

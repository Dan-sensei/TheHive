#version 450

out vec4 frag_colour;

layout(location = 19) uniform sampler2D DiffuseMap;
layout(location = 20) uniform sampler2D DiffuseMap2;
//uniform sampler2D NormalMap;


in vec2 UV;

void main() {

    vec3 MaterialDiffuseColor = texture( DiffuseMap, UV).rgb;
    vec3 MaterialDiffuseColor2 = texture( DiffuseMap2, UV).rgb;
    vec3 MaterialAmbientColor = MaterialDiffuseColor2* MaterialDiffuseColor;

    frag_colour = vec4(
        MaterialAmbientColor ,1);

};

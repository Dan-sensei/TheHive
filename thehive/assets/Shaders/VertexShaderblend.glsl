#version 450

layout(location = 0) in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
//layout(location = 3) in vec3 vertexTangent_modelspace;
//layout(location = 4) in vec3 vertexBitangent_modelspace;


layout(location = 11) uniform mat4 MVP;

out vec2 UV;


void main() {

    gl_Position = MVP*vec4(vertexPosition_modelspace, 1);


    UV = vertexUV;

};

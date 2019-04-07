#version 450 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;

layout(location = 10) uniform mat4 M;
layout(location = 11) uniform mat4 MVP;

out vec3 Position_worldspace;
out mat3 TBN;
out vec2 UV;

void main() {

    gl_Position = MVP*vec4(vertexPosition_modelspace, 1);
    vec4 PosInWorldV4 = M * vec4(vertexPosition_modelspace,1);
    Position_worldspace = PosInWorldV4.xyz;

    UV = vertexUV;

	vec3 T = normalize(M * vec4(vertexTangent_modelspace,0)).xyz;
	vec3 B = normalize(M * vec4(vertexBitangent_modelspace,0)).xyz;
	vec3 N = normalize(M * vec4(vertexNormal_modelspace,0)).xyz;

	TBN = transpose(mat3(T,B,N));
};

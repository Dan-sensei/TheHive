#version 450 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;


layout(location =  9) uniform mat4 M;
layout(location = 10) uniform mat3 NormalMatrix;
layout(location = 11) uniform mat4 MVP;

out float Z;
out mat3 TBN;
out vec2 UV;

void main() {

    vec4 Pos = M * vec4(vertexPosition_modelspace, 1);
    Z = Pos.z;
    gl_Position = MVP*vec4(vertexPosition_modelspace, 1);

    UV = vertexUV;
    
	vec3 T = normalize(NormalMatrix * vertexTangent_modelspace);
	vec3 B = normalize(NormalMatrix * vertexBitangent_modelspace);
	vec3 N = normalize(NormalMatrix * vertexNormal_modelspace);

	TBN = transpose(mat3(T,B,N));
};

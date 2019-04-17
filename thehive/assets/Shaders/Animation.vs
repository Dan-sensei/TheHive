#version 450

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;


layout(location = 5) in vec3 vertexPosition_modelspace1;
layout(location = 6) in vec3 vertexNormal_modelspace1;
layout(location = 7) in vec3 vertexTangent_modelspace1;
layout(location = 8) in vec3 vertexBitangent_modelspace1;

layout(location = 9) uniform mat4 M;
layout(location = 10) uniform mat3 NormalMatrix;
layout(location = 11) uniform mat4 MVP;

layout(location = 18) uniform float TweenFactor;

out float Z;
out mat3 TBN;
out vec2 UV;

void main() {

    vec4 Pos = M * vec4(vertexPosition_modelspace, 1);
    Z = Pos.z;
    vec3 mixPos = mix(vertexPosition_modelspace, vertexPosition_modelspace1, TweenFactor);
    gl_Position = MVP*vec4(mixPos, 1);

    UV = vertexUV;
    //mat3 normalMatrix = transpose(inverse(M));
    //Normal = M * vertexNormal_modelspace;

	vec3 T = normalize(NormalMatrix * mix(vertexTangent_modelspace, vertexTangent_modelspace1, TweenFactor));
	vec3 B = normalize(NormalMatrix * mix(vertexBitangent_modelspace, vertexBitangent_modelspace1, TweenFactor));
	vec3 N = normalize(NormalMatrix * mix(vertexNormal_modelspace, vertexNormal_modelspace1, TweenFactor));

	TBN = transpose(mat3(T,B,N));
};

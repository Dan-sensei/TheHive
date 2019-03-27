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

layout(location = 10) uniform mat4 M;
layout(location = 11) uniform mat4 MVP;
layout(location = 12) uniform vec3 LightPosition_worldspace;
layout(location = 13) uniform vec3 CameraPos;

layout(location = 18) uniform float TweenFactor;

out vec2 UV;
out vec3 Position_worldspace;

out vec3 LightPosT;
out vec3 EyePosT;
out vec3 VertexPosT;

void main() {

    vec3 mixPos = mix(vertexPosition_modelspace, vertexPosition_modelspace1, TweenFactor);
    gl_Position = MVP*vec4(mixPos, 1);
    vec4 PosInWorldV4 = M * vec4(mixPos,1);
    Position_worldspace = PosInWorldV4.xyz;

    UV = vertexUV;

	vec3 T = normalize(M * vec4(mix(vertexTangent_modelspace, vertexTangent_modelspace1, TweenFactor),0)).xyz;
	vec3 B = normalize(M * vec4(mix(vertexBitangent_modelspace, vertexBitangent_modelspace1, TweenFactor),0)).xyz;
	vec3 N = normalize(M * vec4(mix(vertexNormal_modelspace, vertexNormal_modelspace1, TweenFactor),0)).xyz;

	mat3 TBN = transpose(mat3(T,B,N));

    LightPosT = TBN * LightPosition_worldspace;
    EyePosT = TBN * CameraPos;
    VertexPosT = TBN * Position_worldspace;
};

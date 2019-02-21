#version 400

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;

//out vec3 fragmentColor;

uniform mat4 MVP;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;
uniform vec3 CameraPos;

out vec2 UV;
out vec3 Position_worldspace;

out vec3 LightPosT;
out vec3 EyePosT;
out vec3 VertexPosT;

void main() {

    gl_Position = MVP*vec4(vertexPosition_modelspace, 1);
    vec4 PosInWorldV4 = M * vec4(vertexPosition_modelspace,1);
    Position_worldspace = PosInWorldV4.xyz;

    UV = vertexUV;

	vec3 T = normalize(M * vec4(vertexTangent_modelspace,0)).xyz;
	vec3 B = normalize(M * vec4(vertexBitangent_modelspace,0)).xyz;
	vec3 N = normalize(M * vec4(vertexNormal_modelspace,0)).xyz;

	mat3 TBN = transpose(mat3(T,B,N));

    LightPosT = TBN * LightPosition_worldspace;
    EyePosT = TBN * CameraPos;
    VertexPosT = TBN * Position_worldspace;
};

#version 400

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 vertexTangent_modelspace;
layout(location = 4) in vec3 vertexBitangent_modelspace;

//out vec3 fragmentColor;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightPosition_worldspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

out vec3 LightDirection_tangentspace;
out vec3 EyeDirection_tangentspace;

void main() {

    gl_Position = MVP*vec4(vertexPosition_modelspace, 1);
    vec4 PosInWorldV4 = M * vec4(vertexPosition_modelspace,1);

	Position_worldspace = PosInWorldV4.xyz;
    UV = vertexUV;

	vec3 vertexPosition_cameraspace = ( V * PosInWorldV4).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace - vertexPosition_cameraspace;

	vec3 vertexTangent_cameraspace = MV3x3 * vertexTangent_modelspace;
	vec3 vertexBitangent_cameraspace = MV3x3 * vertexBitangent_modelspace;
	vec3 vertexNormal_cameraspace = MV3x3 * vertexNormal_modelspace;

	mat3 TBN = transpose(mat3(
		vertexTangent_cameraspace,
		vertexBitangent_cameraspace,
		vertexNormal_cameraspace
	));

	LightDirection_tangentspace = TBN * LightDirection_cameraspace;
	EyeDirection_tangentspace =  TBN * EyeDirection_cameraspace;

};

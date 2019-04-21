#version 450 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;
layout (location = 3) out vec4 gVelocity;

in float Z;
in mat3 TBN;
in vec2 UV;

in vec4 PreviousPos;
in vec4 CurrentPos;

layout(location = 14) uniform sampler2D DiffuseMap;
layout(location = 15) uniform sampler2D NormalMap;
layout(location = 16) uniform sampler2D SpecularMap;

void main() {

    vec3 NormalMapTexture = texture(NormalMap, UV).rgb * 2.0 - 1.0;
    NormalMapTexture.xy *= 2;
    gNormal = normalize(NormalMapTexture * TBN);
    gAlbedoSpec.rgb = texture(DiffuseMap, UV).rgb;
    gAlbedoSpec.a = texture(SpecularMap, UV).r;

    gPosition.r = Z;

    vec2 C = (CurrentPos.xy / CurrentPos.w) * 0.5 + 0.5;
    vec2 P = (PreviousPos.xy / PreviousPos.w) * 0.5 + 0.5;
    gVelocity.rg = C - P;
};

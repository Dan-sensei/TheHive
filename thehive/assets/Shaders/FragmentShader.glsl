#version 450 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gAlbedoSpec;

in vec3 Position_worldspace;
in mat3 TBN;
in vec2 UV;

layout(location = 14) uniform sampler2D DiffuseMap;
layout(location = 15) uniform sampler2D NormalMap;
layout(location = 16) uniform sampler2D SpecularMap;

void main() {

    gPosition = Position_worldspace;
    vec3 NormalMapTexture = texture(NormalMap, UV).rgb * 2.0 - 1.0;
    NormalMapTexture.xy *= 4;
    gNormal = normalize(NormalMapTexture) * TBN;
    gAlbedoSpec.rgb = texture(DiffuseMap, UV).rgb;
    gAlbedoSpec.a = texture(SpecularMap, UV).r;

};

#version 450 core

out vec4 FragColor;

in vec2 UV;

layout(location = 5) uniform sampler2D gPosition;
layout(location = 6) uniform sampler2D gNormal;
layout(location = 7) uniform sampler2D gDiffuseSpec;


layout(location = 12) uniform vec3 LightPosition_worldspace;
layout(location = 13) uniform vec3 CameraPos;

void main()
{

    vec3 VertexPos = texture(gPosition, UV).rgb;
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Diffuse = texture(gDiffuseSpec, UV).rgb;
    float SpecularTex = texture(gDiffuseSpec, UV).a;

    vec3 LightColor = vec3(1,1,1);
    float LightPower = 150.0f;

    vec3 FinalPixelColor  = Diffuse * 0.1f;

    // Diffuse
    vec3 LightDir = normalize(LightPosition_worldspace - VertexPos);
    vec3 diffuse = clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse * LightPower;

    // Specular
    vec3 E = normalize(CameraPos - VertexPos);
    vec3 halfwayDir = normalize(LightDir + E);
    float cosAlpha = max(dot(Normal, halfwayDir), 0.0);
    // Optimización a pow(cosAlpha, n) = cosAlpha / (n - n*cosAlpha + cosAlpha)
    float spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
    vec3 FinalSpecular = LightColor * spec * SpecularTex * LightPower;

    // Attenuation
    float dist = length(LightPosition_worldspace - VertexPos);
    float attenuation = 1.0 / (dist * dist);

    diffuse *= attenuation;
    FinalSpecular *= attenuation;

    FinalPixelColor += diffuse + FinalSpecular;

    FragColor = vec4(
        FinalPixelColor, 1.0
    );
}

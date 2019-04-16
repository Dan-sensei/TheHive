#version 450 core

out vec4 FragColor;

in vec2 UV;
in vec2 half_ndc_position;


layout(location = 5) uniform sampler2D depthTex;
layout(location = 6) uniform sampler2D gNormal;
layout(location = 7) uniform sampler2D gDiffuseSpec;

layout(location = 12) uniform vec3 LightPosition_worldspace;


vec3 getViewPosition(float Depth) {
    vec3 Position = vec3(half_ndc_position * Depth, Depth);
    return(Position);
}

#define FOG_DENSTITY 0.03f * 0.03f
#define FOG_GRADIENT 0.8f * 0.8f

void main()
{
    vec4 DiffuseTexture = texture(gDiffuseSpec, UV);
    float SpecularTex = DiffuseTexture.a;
    if(SpecularTex == 1){
        FragColor = vec4(60.f/255, 87.f/255, 106.f/255, 1.0f);
        return;
    }

    vec3 VertexPos = getViewPosition(texture(depthTex, UV).r);
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Diffuse = DiffuseTexture.rgb;

    vec3 LightColor = vec3(1,1,1);
    float LightPower = 25.0f;

    vec3 FinalPixelColor  = Diffuse * 0.18f;

    // Diffuse
    vec3 LightDir = normalize(LightPosition_worldspace - VertexPos);
    vec3 diffuse = clamp( dot( Normal, LightDir ), 0, 1 ) * Diffuse * LightPower;

    // Specular
    vec3 E = normalize(-VertexPos);
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

    // Niebla
    float DistanceFromCamera = dot(VertexPos, VertexPos);
    float Base = DistanceFromCamera*FOG_DENSTITY;
    float FogBlendFactor = exp(-(Base / (FOG_GRADIENT - FOG_GRADIENT*Base + Base*0.75)));
    //float FogBlendFactor = exp(-pow(Base, FOG_GRADIENT));
    FogBlendFactor = clamp(FogBlendFactor, 0.0, 1.0);

    FragColor = vec4(
        FinalPixelColor, 1.0
    );

    FragColor = mix(vec4(60.f/255, 87.f/255, 106.f/255, 1.0f), FragColor, FogBlendFactor);

}

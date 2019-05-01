#version 450 core

#define NLUCESF 8
#define NLUCESP 8


layout (std140) uniform light
{
  vec3 dirluzD;
  vec3 colorluzD;
  float intluzD;
  float NNlucesF;
  float NNlucesP;

  vec3 posluzF      [NLUCESF];
  vec3 posfocoluzF  [NLUCESF];
  vec3 colorluzF  [NLUCESF];
  float intluzF  [NLUCESF];

  vec3 posluzP      [NLUCESP];
  vec3 colorluzP  [NLUCESP];
  float intluzP  [NLUCESP];
}luces;


layout (location = 0) out vec4 gRender;

in vec2 UV;
in vec2 half_ndc_position;


layout(binding = 0) uniform sampler2D depthTex;
layout(binding = 1) uniform sampler2D gNormal;
layout(binding = 2) uniform sampler2D gDiffuseSpec;

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

    float dist;
    float attenuation;

    vec3 VertexPos = getViewPosition(texture(depthTex, UV).r);
    vec3 Normal = texture(gNormal, UV).rgb;
    vec3 Diffuse = DiffuseTexture.rgb;

    vec3 LightColor = vec3(1,1,1);
    float LightPowerDir = luces.intluzD;
    float LightPowerFo;// = 150.0f;
    //float LightPower = 25.0f;


    vec3 FinalPixelColor  = Diffuse * 0.18f;

////////// Direccional

vec3 LightDir=luces.dirluzD;//vec3(0,1,0);// la luz del sol
//vec3 LightDir = normalize(luzdir);
vec3 diffuse = clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse *LightPowerDir;
//diffuse =diffuse+ clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse * LightPower;

// Specular
vec3 E = normalize(- VertexPos);
vec3 halfwayDir = normalize(LightDir + E);
float cosAlpha = max(dot(Normal, halfwayDir), 0.0);
// Optimización a pow(cosAlpha, n) = cosAlpha / (n - n*cosAlpha + cosAlpha)
float spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
//FinalSpecular =FinalSpecular+ LightColor * spec * SpecularTex * LightPower;
vec3 FinalSpecular = LightColor * spec * SpecularTex *LightPowerDir;
////////
////////////////////////////////////////////////////////////////

//luz puntual de prueba

LightColor = vec3(1,1,1);
float LightPower = 150.0f;
////////////////////////////////////////////////////////////
vec3 posluz=LightPosition_worldspace;


//FinalPixelColor  = Diffuse * 0.18f;

// Diffuse
LightDir = normalize(posluz - VertexPos);
diffuse = clamp( dot( Normal, LightDir ), 0, 1 ) * Diffuse * LightPower;

// Specular
E = normalize(-VertexPos);
halfwayDir = normalize(LightDir + E);
cosAlpha = max(dot(Normal, halfwayDir), 0.0);
// Optimización a pow(cosAlpha, n) = cosAlpha / (n - n*cosAlpha + cosAlpha)
spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
FinalSpecular = LightColor * spec * SpecularTex * LightPower;

// Attenuation
dist = length(posluz - VertexPos);
attenuation = 1.0 / (dist * dist);

diffuse *= attenuation;
FinalSpecular *= attenuation;

////////////////////////////////
/*
//luz puntual real
for(int i = 0;  i< NLUCESP; i++)
{


}
//luz focal
vec3 luzp1;
vec3 luzp2;
vec3 dir;
vec3 LightDir1;
float eff;
vec3 diffuse2;
vec3 FinalSpecular2;
float att2;
//att2=(0.1-(1-eff))/0.1;//0.1-->0//0-->1
for(int i = 0;  i< NLUCESF; i++)
{
     luzp1=luces.posluzF[i];
     luzp2=luces.posfocoluzF[i];
     LightPowerFo=luces.intluzF[i];
     LightColor=luces.colorluzF[i];

    //dir=normalize(luzp2-luzp1);
    dir=luzp2;
    //vec3 dir=vec3(0,1,0);
    LightDir1 = normalize( VertexPos-luzp1);
    eff=dot(LightDir1,dir);
    if(eff>0.9){
        att2=(0.1-(1-eff))/0.1;//0.1-->0//0-->1
        // Diffuse
        LightDir = normalize(luzp1 - VertexPos);
        diffuse2 = clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse * LightPowerFo;
         //diff = max(dot(normal, lightDir), 0.0);

        // Specular
        //E = normalize(CameraPos - VertexPos);
        halfwayDir = normalize(LightDir + E);
        cosAlpha = max(dot(Normal, halfwayDir), 0.0);
        // Optimización a pow(cosAlpha, n) = cosAlpha / (n - n*cosAlpha + cosAlpha)
        spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
        FinalSpecular2 = LightColor * spec * SpecularTex * LightPowerFo;

        // Attenuation
        dist = length(luzp1 - VertexPos);
        attenuation = 1.0 / (dist * dist);

        diffuse2 *= attenuation*att2;
        FinalSpecular2 *= attenuation*att2;

        diffuse += diffuse2;
        FinalSpecular += FinalSpecular2;

    //FinalPixelColor += diffuse + FinalSpecular;
    }
}
*/
    FinalPixelColor += diffuse + FinalSpecular;



    // Niebla
    float DistanceFromCamera = dot(VertexPos, VertexPos);
    float Base = DistanceFromCamera*FOG_DENSTITY;
    float FogBlendFactor = exp(-(Base / (FOG_GRADIENT - FOG_GRADIENT*Base + Base*0.75)));
    //float FogBlendFactor = exp(-pow(Base, FOG_GRADIENT));
    FogBlendFactor = clamp(FogBlendFactor, 0.0, 1.0);

    gRender = vec4(FinalPixelColor, 1.0);
    gRender = mix(vec4(60.f/255, 87.f/255, 106.f/255, 1.0), gRender, FogBlendFactor);

}

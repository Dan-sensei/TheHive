#version 450 core

#define NLUCESF 8
#define NLUCESP 16


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


vec3 getViewPosition(float Depth) {
    vec3 Position = vec3(half_ndc_position * Depth, Depth);
    return(Position);
}

#define FOG_DENSTITY 0.03f * 0.03f
#define FOG_GRADIENT 0.8f * 0.8f


#define FOG_COLOR vec4(42,42,42, 1)
#define NormFogColor vec4(FOG_COLOR.x/255.f, FOG_COLOR.y/255.f, FOG_COLOR.z/255.f, 1.f)

void main()
{
    vec4 DiffuseTexture = texture(gDiffuseSpec, UV);
    float SpecularTex = DiffuseTexture.a;
    if(SpecularTex == 1){
        gRender = NormFogColor;
        return;
    }

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

    // ================================== Direccional ==================================
        vec3 LightDir=luces.dirluzD;//vec3(0,1,0);// la luz del sol
        //vec3 LightDir = normalize(luzdir);
        vec3 DIFFUSE = clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse *LightPowerDir;
        //diffuse =diffuse+ clamp( dot( Normal, LightDir ), 0,1 ) * Diffuse * LightPower;

        // Specular
        vec3 E = normalize(- VertexPos);
        vec3 halfwayDir = normalize(LightDir + E);
        float cosAlpha = max(dot(Normal, halfwayDir), 0.0);
        // Optimización a pow(cosAlpha, n) = cosAlpha / (n - n*cosAlpha + cosAlpha)
        float spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
        //FinalSpecular =FinalSpecular+ LightColor * spec * SpecularTex * LightPower;
        vec3 SPECULAR = LightColor * spec * SpecularTex *LightPowerDir;
    // ==================================================================================


    // ================================== POINT LIGHTS ==================================
    for(int i = 0;  i < luces.NNlucesP; i++) {

        LightColor = luces.colorluzP[i];
        float LightPower = luces.intluzP[i];
        vec3 posluz = luces.posluzP[i];

        // Diffuse
        LightDir = normalize(posluz - VertexPos);
        vec3 PointDiffuse = clamp( dot( Normal, LightDir ), 0, 1 ) * Diffuse * LightPower * LightColor;

        // Specular
        halfwayDir = normalize(LightDir + E);
        cosAlpha = max(dot(Normal, halfwayDir), 0.0);
        // Optimización a pow(base, e) = base / (e - e*base + base)
        spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
        vec3 SpecularPoint = LightColor * spec * SpecularTex * LightPower;

        // Attenuation
        dist = length(posluz - VertexPos);
        attenuation = 1.0 / (dist * dist);

        DIFFUSE += PointDiffuse * attenuation;
        SPECULAR += SpecularPoint * attenuation;
    }
    // ==================================================================================


    // ================================== FOCAL LIGHTS ==================================
    vec3 luzp1;
    vec3 luzp2;
    vec3 dir;
    vec3 LightDir1;
    float eff;
    vec3 diffuse2;
    vec3 FinalSpecular2;
    float att2;
    for(int i = 0;  i < luces.NNlucesF; i++)
    {
        luzp1 = luces.posluzF[i];
        luzp2 = luces.posfocoluzF[i];
        LightPowerFo = luces.intluzF[i];
        LightColor=luces.colorluzF[i];

        dir = normalize(luzp1 - luzp2);

        LightDir1 = normalize(  luzp1 - VertexPos );
        eff = dot(LightDir1,dir);
        if(eff > 0.9) {
            att2=(0.1-(1-eff))/0.1; //0.1-->0//0-->1
            // Diffuse
            diffuse2 = clamp( dot( Normal, LightDir1 ), 0,1 ) * Diffuse * LightPowerFo * LightColor;

            // Specular
            halfwayDir = normalize(LightDir1 + E);
            cosAlpha = max(dot(Normal, halfwayDir), 0.0);
            spec = cosAlpha/(16 - 16 * cosAlpha + cosAlpha);
            FinalSpecular2 = LightColor * spec * SpecularTex * LightPowerFo;

            // Attenuation
            dist = length(luzp1 - VertexPos);
            attenuation = 1.0 / (dist * dist);

            diffuse2 *= attenuation*att2;
            FinalSpecular2 *= attenuation*att2;

            DIFFUSE += diffuse2;
            SPECULAR += FinalSpecular2;
        }
    }
    // ==================================================================================


    FinalPixelColor += DIFFUSE + SPECULAR;


    // Niebla
    float DistanceFromCamera = dot(VertexPos, VertexPos);
    float Base = DistanceFromCamera*FOG_DENSTITY;
    float FogBlendFactor = exp(-(Base / (FOG_GRADIENT - FOG_GRADIENT*Base + Base*0.75)));
    //float FogBlendFactor = exp(-pow(Base, FOG_GRADIENT));
    FogBlendFactor = clamp(FogBlendFactor, 0.0, 1.0);

    gRender = vec4(FinalPixelColor, 1.0);
    gRender = mix(NormFogColor, gRender, FogBlendFactor);

}

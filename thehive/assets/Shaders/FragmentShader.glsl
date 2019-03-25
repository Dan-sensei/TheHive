#version 450 core

out vec4 frag_colour;

layout(location = 12) uniform vec3 LightPosition_worldspace;

layout(location = 14) uniform sampler2D DiffuseMap;
layout(location = 15) uniform sampler2D NormalMap;
layout(location = 16) uniform sampler2D SpecularMap;

in vec2 UV;
in vec3 Position_worldspace;

in vec3 LightPosT;
in vec3 EyePosT;
in vec3 VertexPosT;


#define BASE_FACTOR 0.2

void main() {

    vec4 tex = texture(DiffuseMap,UV);
    float color = tex.a;
    // Light emission properties
    // You probably want to put them as uniforms
    vec3 LightColor = vec3(255,255,255);
    LightColor = normalize(LightColor);
    float LightPower = 150.0f;


    // Material properties
    vec3 MaterialDiffuseColor = tex.rgb;
    vec3 MaterialAmbientColor = vec3(BASE_FACTOR) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = texture( SpecularMap, UV ).rgb * 0.3;
    vec3 TextureNormal_tangentspace = normalize(texture2D( NormalMap, vec2(UV.x,-UV.y)).rgb*2.0 - 1.0);

    float dist = length( LightPosition_worldspace - Position_worldspace );
    vec3 n = TextureNormal_tangentspace;
    vec3 l = normalize( LightPosT - VertexPosT );
    float cosTheta = clamp( dot( n,l ), 0,1 );
    vec3 E = normalize(EyePosT - VertexPosT);
    vec3 R = reflect(-l,n);
    float cosAlpha = clamp( dot( E,R ), 0,1 );

    frag_colour = vec4(
        // Ambient : simulates indirect lighting
        MaterialAmbientColor +
        // Diffuse : "color" of the object
        MaterialDiffuseColor * LightColor * LightPower * cosTheta / (dist*2) +
        // Specular : reflective highlight, like a mirror
        MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (dist*dist), color);

};

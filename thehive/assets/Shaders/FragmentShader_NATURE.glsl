#version 400

out vec4 frag_colour;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;

in vec2 UVFromGeom;
in vec3 Position_worldspaceFromGeom;

in vec3 LightPosTFromGeom;
in vec3 EyePosTFromGeom;
in vec3 VertexPosTFromGeom;

uniform vec3 LightPosition_worldspace;

#define BASE_FACTOR 0.2

void main() {


  // Light emission properties
  // You probably want to put them as uniforms
  vec3 LightColor = vec3(255,255,255);
  LightColor = normalize(LightColor);
  float LightPower = 150.0f;

  // Material properties
  vec3 MaterialDiffuseColor = texture( DiffuseMap, UVFromGeom).rgb;
  vec3 MaterialAmbientColor = vec3(BASE_FACTOR) * MaterialDiffuseColor;
  vec3 MaterialSpecularColor = texture( SpecularMap, UVFromGeom ).rgb * 0.3;
  vec3 TextureNormal_tangentspace = normalize(texture2D( NormalMap, vec2(UVFromGeom.x,-UVFromGeom.y)).rgb*2.0 - 1.0);

  float dist = length( LightPosition_worldspace - Position_worldspaceFromGeom );
  vec3 n = TextureNormal_tangentspace;
  vec3 l = normalize( LightPosTFromGeom - VertexPosTFromGeom );
  float cosTheta = clamp( dot( n,l ), 0,1 );
  vec3 E = normalize(EyePosTFromGeom - VertexPosTFromGeom);
  vec3 R = reflect(-l,n);
  float cosAlpha = clamp( dot( E,R ), 0,1 );

  frag_colour = vec4(
      // Ambient : simulates indirect lighting
      MaterialAmbientColor +
      // Diffuse : "color" of the object
      MaterialDiffuseColor * LightColor * LightPower * cosTheta / (dist*dist) +
      // Specular : reflective highlight, like a mirror
      MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (dist*dist),1);

};

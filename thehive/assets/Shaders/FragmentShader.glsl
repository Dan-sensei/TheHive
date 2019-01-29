#version 400

out vec4 frag_colour;

uniform sampler2D DiffuseTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform sampler2D SpecularTextureSampler;

in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;

uniform vec3 LightPosition_worldspace;

void main() {


  // Light emission properties
  // You probably want to put them as uniforms
  vec3 LightColor = vec3(255,255,255);
  LightColor = normalize(LightColor);
  float LightPower = 150.0f;

  // Material properties
  vec3 MaterialDiffuseColor = texture( DiffuseTextureSampler, UV, -1.2 ).rgb;
  vec3 MaterialAmbientColor = vec3(0.04,0.04,0.04) * MaterialDiffuseColor;
  vec3 MaterialSpecularColor = texture( SpecularTextureSampler, UV ).rgb * 0.3;
  vec3 TextureNormal_tangentspace = normalize(texture( NormalTextureSampler, vec2(UV.x,-UV.y), -1.2 ).rgb*2.0 - 1.0);

  float distance = length( LightPosition_worldspace - Position_worldspace );
  vec3 n = TextureNormal_tangentspace;
  vec3 l = normalize( LightDirection_tangentspace );
  float cosTheta = clamp( dot( n,l ), 0,1 );
  vec3 E = normalize(EyeDirection_tangentspace);
  vec3 R = reflect(-l,n);
  float cosAlpha = clamp( dot( E,R ), 0,1 );

  frag_colour = vec4(
      // Ambient : simulates indirect lighting
      MaterialAmbientColor +
      // Diffuse : "color" of the object
      MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
      // Specular : reflective highlight, like a mirror
      MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance),1);

};

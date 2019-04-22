#version 450


in vec2 UV;
in vec4 ParticleColor;

out vec4 frag_colour;

layout(binding = 0) uniform sampler2D ParticleTexture;

void main(){
	vec4 ParticleTexture = texture( ParticleTexture, UV );

	frag_colour = ParticleColor;
}

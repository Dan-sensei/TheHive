#version 450


in vec2 UV;
in vec4 ParticleColor;

out vec4 frag_colour;

layout(location = 14) uniform sampler2D ParticleTexture;

void main(){
	frag_colour = texture( ParticleTexture, UV ) * ParticleColor;
}

#version 450


in vec2 UV;
in vec4 ParticleColor;

out vec4 frag_colour;

layout(binding = 0) uniform sampler2D ZBuffer;
layout(binding = 1) uniform sampler2D ParticleTexture;

void main() {
	frag_colour = texture( ParticleTexture, UV ) * ParticleColor;
}
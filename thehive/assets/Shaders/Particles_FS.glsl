#version 450


in vec2 UV;
in vec4 ParticleColor;

out vec4 frag_colour;

layout(location = 14) uniform sampler2D ParticleTexture;

void main(){
	vec4 ParticleTexture = texture( ParticleTexture, UV );
	
	if(ParticleTexture.a == 0)
		discard;

	frag_colour = ParticleTexture;
}

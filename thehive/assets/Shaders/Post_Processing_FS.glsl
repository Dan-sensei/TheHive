#version 450 core

out vec4 FragColor;

in vec2 UV;

layout(location = 5) uniform sampler2D RenderTexture;
layout(location = 6) uniform sampler2D VelocityTexture;

layout(location = 7) uniform float BlurFactor;

#define MAX_SAMPLES 20

void main() {

    vec2 texelSize = 1.0 / vec2(textureSize(RenderTexture, 0));

    vec2 velocity = texture(VelocityTexture, UV).rg;
    velocity *= BlurFactor*0.7;

    float speed = length(velocity / texelSize);
    int Samples = clamp(int(speed), 1, MAX_SAMPLES);

    vec4 FinalColor = texture(RenderTexture, UV);

    for (int i = 1; i < Samples; ++i) {
        vec2 offset = velocity * (float(i) / float(Samples - 1) - 0.5);
        vec2 offsetUV = clamp(UV + offset, 0, 1);
        FinalColor += texture(RenderTexture, offsetUV);
    }

    FinalColor /= float(Samples);

    FragColor = FinalColor;
}

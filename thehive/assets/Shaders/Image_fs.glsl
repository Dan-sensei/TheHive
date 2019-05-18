#version 450

layout(binding = 0) uniform sampler2D Image;

in vec2 UV;

out vec4 Outo;

void main() {
    Outo = texture(Image, UV);
};

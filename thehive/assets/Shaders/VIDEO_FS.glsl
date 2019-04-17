#version 450 core

out vec4 FragColor;

in vec2 UV;

layout(location = 5) uniform sampler2D FRAME;

void main() {
    vec4 Texture_Frame = texture(FRAME, UV);
    FragColor = Texture_Frame;
}

#version 450

layout(location = 0) in vec3 SQUARE;
layout(location = 1) in vec4 Position_Size;
layout(location = 2) in vec4 Color;

layout(location =  9) uniform mat4 MV;
layout(location = 21) uniform mat4 VP;
layout(location = 22) uniform vec3 CameraUP;
layout(location = 23) uniform vec3 CameraRIGHT;

out vec2 UV;
out vec4 ParticleColor;
void main() {

    vec3 CenterPosition = Position_Size.xyz;
    float ParticleSize = Position_Size.w;

    vec3 VertexPosition =
        CenterPosition
        + CameraRIGHT * SQUARE.x * ParticleSize
        + CameraUP * SQUARE.y * ParticleSize;

    vec4 Pos = MV * vec4(VertexPosition, 1.0f);
    gl_Position = VP * vec4(VertexPosition, 1.0f);

    UV = SQUARE.xy + vec2(0.5, 0.5);
    ParticleColor = Color;

};

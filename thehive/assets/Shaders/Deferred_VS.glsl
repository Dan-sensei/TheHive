#version 450 core

layout (location = 0) in vec2 vertexPosition;
layout (location = 1) in vec2 vertexUV;

layout (location = 2) uniform vec2 halfSizeNearPlane;

out vec2 UV;
out vec2 half_ndc_position;

void main()
{
    UV = vertexUV;
    gl_Position = vec4(vertexPosition, 0.0, 1.0);

    //eyeDirection = vec3((2.0 * halfSizeNearPlane * UV) - halfSizeNearPlane , -1.0);

    half_ndc_position = vec2(0.5) - UV;
    half_ndc_position *= halfSizeNearPlane;

}

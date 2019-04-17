/*#version 400

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;
uniform float Zindex;
uniform vec3 particleCenter_wordspace;
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;

out vec2 Texcoord;

void main() {


vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * position.x //* BillboardSize.x
    + CameraUp_worldspace * position.y; //* BillboardSize.y;

    Texcoord=texcoord;
    gl_Position = vec4(vertexPosition_worldspace, 1.0);
};gl_Position
*/
#version 400

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texcoord;
uniform float Zindex;
uniform vec3 particleCenter_wordspace;
uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;

out vec2 Texcoord;
uniform mat4 M;
uniform mat4 MVP;
void main()
{
    //particleCenter_wordspace
    //vec4 centro1 = MVP*vec4(particleCenter_wordspace, 1);
    //vec3 centro=centro1.xyz;

    vec3 vertexPosition_worldspace =
    particleCenter_wordspace+
    CameraRight_worldspace*position.x+
    CameraUp_worldspace*position.y;
    Texcoord=texcoord;
    gl_Position = MVP*vec4(vertexPosition_worldspace, 1);
    //gl_Position = vec4(vertexPosition_worldspace, 1.0);
};

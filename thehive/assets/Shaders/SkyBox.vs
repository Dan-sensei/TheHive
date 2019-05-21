#version 450
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

//uniform mat4 projection;
layout (location = 1) uniform mat4 VP;

void main()
{
    vec4 pos = VP * vec4(aPos, 1.0);
    TexCoords = aPos;
    gl_Position =  pos.xyww;
}

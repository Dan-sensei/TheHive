#version 400
// #extension GL_ARB_explicit_attrib_location : require
// #extension GL_ARB_explicit_uniform_location : require

layout (triangles) in;
// layout (points, max_vertices = 256) out;
// layout (line_strip, max_vertices = 256) out;
layout (triangle_strip, max_vertices = 256) out;

uniform mat4 MVP;
uniform mat4 M;
uniform vec3 LightPosition_worldspace;
uniform vec3 CameraPos;

uniform int  GS_SIZE;
uniform vec3 GS_POSITIONS[48];

in vec2 UV[];
out vec2 UVFromGeom;

in vec3 Position_worldspace[];
out vec3 Position_worldspaceFromGeom;

in vec3 LightPosT[];
out vec3 LightPosTFromGeom;

in vec3 EyePosT[];
out vec3 EyePosTFromGeom;

in vec3 VertexPosT[];
out vec3 VertexPosTFromGeom;


#define _INDEX 0

void main() {
    UVFromGeom = UV[_INDEX];
    Position_worldspaceFromGeom = Position_worldspace[_INDEX];
    LightPosTFromGeom = LightPosT[_INDEX];
    EyePosTFromGeom = EyePosT[_INDEX];
    VertexPosTFromGeom = VertexPosT[_INDEX];

    vec4 position;
    float TAM = 0.1;

    position = gl_in[0].gl_Position;

    for(int i=0 ; i<GS_SIZE ; i+=2){
        gl_Position = position + vec4(GS_POSITIONS[i].xyz, 0.0);
        EmitVertex();

    }
    EndPrimitive();

    // position = gl_in[0].gl_Position;
    // gl_Position = position + vec4(-TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 1:bottom-left
    // EmitVertex();
    // gl_Position = position + vec4( TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 2:bottom-right
    // EmitVertex();
    // gl_Position = position + vec4(-TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 3:top-left
    // EmitVertex();
    // gl_Position = position + vec4( TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 4:top-right
    // EmitVertex();
    // gl_Position = position + vec4( 0.0,  TAM, 0.0, 0.0);    // 5:top
    // EmitVertex();
    //
    // EndPrimitive();











    // for(int i = 0; i < gl_in.length(); i++)
    // {
    //     position = gl_in[i].gl_Position;
    //     gl_Position = position + vec4(-TAM/2.f, -TAM/2.f, 0.0, 0.0);
    //     EmitVertex();
    //     gl_Position = position + vec4(TAM/2.f, -TAM/2.f, 0.0, 0.0);
    //     EmitVertex();
    // }
    // EndPrimitive();


    // position = gl_in[0].gl_Position;
    // gl_Position = position + vec4(-TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 1:bottom-left
    // EmitVertex();
    // gl_Position = position + vec4( TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 2:bottom-right
    // EmitVertex();
    // gl_Position = position + vec4(-TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 3:top-left
    // EmitVertex();
    // gl_Position = position + vec4( TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 4:top-right
    // EmitVertex();
    // gl_Position = position + vec4( 0.0,  TAM, 0.0, 0.0);    // 5:top
    // EmitVertex();
    //
    // EndPrimitive();

    // for(int i=0; i<gl_in.length(); i++){
    //     position = gl_in[i].gl_Position;
    //     gl_Position = position + vec4(-TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 1:bottom-left
    //     EmitVertex();
    //     gl_Position = position + vec4( TAM/2.f, -TAM/2.f, 0.0, 0.0);    // 2:bottom-right
    //     EmitVertex();
    //     gl_Position = position + vec4(-TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 3:top-left
    //     EmitVertex();
    //     gl_Position = position + vec4( TAM/2.f,  TAM/2.f, 0.0, 0.0);    // 4:top-right
    //     EmitVertex();
    //     gl_Position = position + vec4( 0.0,  TAM, 0.0, 0.0);    // 5:top
    //     EmitVertex();
    // }
    // EndPrimitive();
}

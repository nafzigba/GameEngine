// Targeting version 4.5 of GLSL. 
#version 460 core

layout (location = 100) uniform mat4 projectionMatrix; 
layout (location = 101) uniform mat4 viewMatrix; 
layout (location = 102) uniform mat4 modelMatrix;


//layout (location = 500) uniform vec4 objectColor;
out vec4 vsColor;

layout(location = 0) in vec4 vertexPosition;
//layout(location = 12) in vec4 vertexColor;

void main()
{
     // Index into our array using gl_VertexID
    gl_Position = projectionMatrix * viewMatrix * modelMatrix* vertexPosition;
    //vsColor = objectColor;
}
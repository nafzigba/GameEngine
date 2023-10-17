// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	
};

out vec3 worldPosition;
out vec3 worldNormal;
//layout (location = 500) uniform vec4 objectColor;

layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexNormal;
layout(location = 12) in vec4 vertexColor;
layout(location = 2) in vec2 textCoord;
out vec2 texCoord;

void main()
{
     // Index into our array using gl_VertexID
    gl_Position = projectionMatrix * viewMatrix * modelMatrix* vertexPosition;
	worldPosition = (modelMatrix*vertexPosition).xyz;
	worldNormal = normalize(mat3(normalModelMatrix) * vertexNormal.xyz);
	texCoord = textCoord;
}
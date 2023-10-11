// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};
layout (shared) uniform lightBlock
{
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
};
struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
};

layout (shared) uniform materialBlock
{
	Material obj;
};



out vec4 worldPosition;
out vec3 worldNormal;
//layout (location = 500) uniform vec4 objectColor;

layout(location = 0) in vec4 vertexPosition;
layout(location = 0) in vec4 vertexNormal;
layout(location = 12) in vec4 vertexColor;

void main()
{
     // Index into our array using gl_VertexID
    gl_Position = projectionMatrix * viewMatrix * modelMatrix* vertexPosition;
	worldPosition = modelMatrix*vertexPosition;
	worldNormal = (normalModelMatrix * vertexNormal).xyz;
}
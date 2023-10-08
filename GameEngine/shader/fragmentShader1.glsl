// Targeting version 4.5 of GLSL. 
#version 460 core

in vec4 worldPosition;
in vec3 worldNormal;
layout (location = 500) uniform vec4 vsColor;
out vec4 fragmentColor;

layout(shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

struct Material
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
};
layout (shared) uniform MaterialBlock
{
	Material obj;
};

vec4 ambientMat;
vec4 diffuseMat;
vec4 specularMat;
vec4 emmissiveMat;
float specularExp;

vec4 ambientColor;
vec4 diffuseColor;
vec4 specularColor;
vec4 posOrDir;
vec4 lightPos = vec4(10.0f,10.0f,10.0f,1.0f);

void main()
{
	
	//illumColor += specularColor*specularMat;
	
	fragmentColor = illumColor;
}
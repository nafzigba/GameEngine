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
	ambientColor = vec4(0.0f,.5f,.10f,1.0f);
	diffuseColor = vec4(0.0f,1.0f,.10f,1.0f);
	specularColor = vec4(1.0f,1.0f,1.0f,1.0f);

	ambientMat = vec4(0.0f,1.0f,0.0f,1.0f);
	diffuseMat = vec4(0.0f,1.0f,0.0f,1.0f);
	specularMat = vec4(0.9f,1.0f,0.9f,1.0f);
	emmissiveMat = vec4(0.1f,0.1f,0.1f,1.0f);

	specularExp = 256;
	vec4 illumColor = emmissiveMat;
	//vec3 lightVector = vec3(0.0f,0.0f,-1.0f);
	illumColor += ambientColor*ambientMat;
	vec3 lightVector = normalize(lightPos.xyz-worldPosition.xyz);
	illumColor += max(0,dot(lightVector,worldNormal)) * diffuseColor * diffuseMat; 
	//illumColor += specularColor*specularMat;
	
	fragmentColor = illumColor;
}
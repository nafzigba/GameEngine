// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
};
layout (shared) uniform materialBlock
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

layout (shared) uniform MaterialBlock
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
	ambientColor = vec4(0.0f,.5f,.10f,1.0f);
	diffuseColor = vec4(0.0f,1.0f,.10f,1.0f);
	specularColor = vec4(1.0f,1.0f,1.0f,1.0f);

	ambientMat = vec4(0.0f,1.0f,0.0f,1.0f);
	diffuseMat = vec4(0.0f,1.0f,0.0f,1.0f);
	specularMat = vec4(0.9f,1.0f,0.9f,1.0f);
	//emmissiveMat = vec4(0.1f,0.1f,0.1f,1.0f);

	specularExp = 256;
	vec4 illumColor = emmissiveMat;
	//vec3 lightVector = vec3(0.0f,0.0f,-1.0f);
	illumColor += ambientColor*ambientMat;
	vec3 lightVector = normalize(lightPos.xyz-worldPosition.xyz);
	illumColor += max(0,dot(lightVector,worldNormal)) * diffuseColor * diffuseMat; 
}
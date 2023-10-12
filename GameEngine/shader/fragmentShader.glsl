// Targeting version 4.5 of GLSL. 
#version 460 core

in vec3 worldPosition;
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
layout (shared) uniform materialBlock
{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
};

layout(shared) uniform lightBlock{
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
	vec4 posLight;
	vec4 dirLight;
};

void main()
{
	vec4 illumColor = emmissiveMat;

	//vec3 lightVector = vec3(0.0f,0.0f,-1.0f);
	illumColor +=   ambientColor * ambientMat;
	vec3 lightVector1 = normalize( posLight.xyz-worldPosition.xyz);

	illumColor += max(0.0,dot(lightVector1,worldNormal)) *  diffuseColor *  diffuseMat /2; 
	illumColor += max(0,dot(dirLight.xyz,worldNormal)) *  diffuseColor *  diffuseMat /2; 
	
	vec3 viewVector = normalize(worldEyePosition.xyz - worldPosition.xyz);
	vec3 normal = normalize(worldNormal); // Normal vector for the fragment
    vec3 halfwayVector1 = normalize(lightVector1 + viewVector);
	vec3 halfwayVector2 = normalize(dirLight.xyz + viewVector);

	illumColor += ( specularColor* specularMat)*pow(max(dot(normal, halfwayVector1), 0.0f),  specularExp)/2;
	illumColor += ( specularColor* specularMat)*pow(max(dot(normal, halfwayVector2), 0.0),  specularExp)/2;
	//illumColor.z =  1.0f;
	fragmentColor = illumColor;
	
	//fragmentColor = ambientColor;
}
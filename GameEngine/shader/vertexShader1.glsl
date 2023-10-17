// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat4 normalModelMatrix;
	mat4 viewMatrix;
	mat4 projectionMatrix;
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
{/*
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;
	*/
	Material mattttt;
};

layout(shared) uniform lightBlock{
	vec4 ambientColor;
	vec4 diffuseColor;
	vec4 specularColor;
	vec4 posLight;
	vec4 dirLight;
};
layout(shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

out vec4 worldPosition;
out vec3 worldNormal;
out vec4 vsColor;
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
	//vec4 tempColor = texture(sampler, texCoord.st);
	vec4 illumColor = mattttt.emmissiveMat;

	//vec3 lightVector = vec3(0.0f,0.0f,-1.0f);
	illumColor +=   ambientColor * mattttt.ambientMat;
	vec3 lightVector1 = normalize( posLight.xyz-worldPosition.xyz);
	float attenuation = (1/pow(distance(posLight.xyz,worldPosition.xyz),2));
	illumColor += attenuation*max(0,dot(lightVector1,worldNormal.xyz)) *  diffuseColor *  mattttt.diffuseMat /2; 
	illumColor += max(0,dot(normalize(dirLight.xyz),worldNormal.xyz)) *  diffuseColor *  mattttt.diffuseMat /2; 
	
	vec3 viewVector = normalize(worldEyePosition.xyz - worldPosition.xyz);
	vec3 normal = normalize(worldNormal); // Normal vector for the fragment
    vec3 halfwayVector1 = normalize(lightVector1 + viewVector);
	vec3 halfwayVector2 = normalize(dirLight.xyz + viewVector);

	illumColor += ( specularColor* mattttt.specularMat)*pow(max(dot(normal, halfwayVector1), 0.0f),  mattttt.specularExp)/2;
	illumColor += ( specularColor* mattttt.specularMat)*pow(max(dot(normal, halfwayVector2), 0.0),  mattttt.specularExp)/2;
	//illumColor.z =  1.0f;
	//fragmentColor = tempColor;
	//illumColor.z =  1.0f;
	vsColor = illumColor;
}
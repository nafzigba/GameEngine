// Targeting version 4.5 of GLSL. 
#version 460 core

layout(shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};


layout (location = 500) uniform vec4 objectColor;
out vec4 fragmentColor;

void main()
{
	fragmentColor = objectColor;

}
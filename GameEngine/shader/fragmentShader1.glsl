// Targeting version 4.5 of GLSL. 
#version 460 core

out vec4 fragmentColor;

in vec4 vsColor;

void main()
{
	fragmentColor = vsColor;
}
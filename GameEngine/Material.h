#pragma once

#include "MathLibsConstsFuncs.h"

using namespace constants_and_types;

struct Material
{
	vec4 ambientMat = vec4(0.05f,0.05f,0.05f,1.0f);
	vec4 diffuseMat = vec4(0.10f, 0.10f, 0.10f, 1.0f);;
	vec4 specularMat = vec4(0.50f, 0.50f, 0.50f, 1.0f);;
	vec4 emmissiveMat = vec4(0.0f, 0.0f, 0.0f, 1.0f);;
	float specularExp = 256;
	GLuint textureObject = 0;
};

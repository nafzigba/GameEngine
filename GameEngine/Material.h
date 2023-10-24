#pragma once

#include "MathLibsConstsFuncs.h"

using namespace constants_and_types;

struct Material
{
	vec4 ambientMat = vec4(0.05f,0.05f,0.05f,1.0f);
	vec4 diffuseMat = vec4(0.30f, 0.30f, 0.30f, 1.0f);;
	vec4 specularMat = vec4(01.0f, 01.0f, 01.0f, 1.0f);;
	vec4 emmissiveMat = vec4(0.0f, 0.0f, 0.0f, 1.0f);;
	float specularExp = 256;
	GLuint textureObject = 0;
};

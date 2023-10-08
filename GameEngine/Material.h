#pragma once

#include "MathLibsConstsFuncs.h"

using namespace constants_and_types;

struct Material
{
	vec4 basicColor;
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	vec4 emmissiveMat;
	float specularExp;

};

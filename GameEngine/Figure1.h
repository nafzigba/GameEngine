#pragma once
#include "MeshComponent.h"
using namespace std;
class Figure1 : public MeshComponent{
public:
	Figure1(GLuint shaderProgram, int 	updateOrder);
	virtual void buildMesh(vector<vec4> &ptData);
};


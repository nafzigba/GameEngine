#pragma once
#include "MeshComponent.h"
class Figure2 : public MeshComponent{
public:
	Figure2(GLuint shaderProgram, int 	updateOrder);
	virtual void buildMesh() override;
};


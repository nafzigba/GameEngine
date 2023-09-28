#pragma once
#include "MeshComponent.h"
class Figure3 : public MeshComponent{
public:
	Figure3(GLuint shaderProgram, int 	updateOrder);
	virtual void buildMesh() override;
};


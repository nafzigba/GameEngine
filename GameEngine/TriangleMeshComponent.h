#pragma once
#include "MeshComponent.h"
class TriangleMeshComponent : public MeshComponent {
public:
    TriangleMeshComponent(GLuint shaderProgram, int updateOrder);
    virtual void buildMesh() override;
};


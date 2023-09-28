#pragma once
#include "MeshComponent.h"
using namespace std;
class TriangleMeshComponent : public MeshComponent {
public:
    TriangleMeshComponent(GLuint shaderProgram, int updateOrder);
    virtual void buildMesh() override;
};


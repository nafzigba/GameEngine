#pragma once
#include "MeshComponent.h"
using namespace std;

class TriangleMeshComponent1 : public MeshComponent {
public:
    TriangleMeshComponent1(GLuint shaderProgram, int updateOrder);
    virtual void buildMesh() override;
    void orderedMesh1();
    void orderedMesh2();
    void addTriangle(const vector<vec4>& triangleVertices);
};


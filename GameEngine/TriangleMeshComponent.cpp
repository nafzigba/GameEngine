#include "TriangleMeshComponent.h"
TriangleMeshComponent::TriangleMeshComponent(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void TriangleMeshComponent::buildMesh()
{
	SubMesh subMesh;
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);

	subMesh.primitiveMode = GL_TRIANGLES;
	subMesh.renderMode = ORDERED;
	subMesh.count = 3;

	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);
}

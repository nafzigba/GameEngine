#include "TriangleMeshComponent.h"
TriangleMeshComponent::TriangleMeshComponent(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void TriangleMeshComponent::buildMesh()
{
	SubMesh subMesh;
	/*
	const vec4 vtcs[3] = { vec4(-0.25, -0.25, 0.0, 1.0),
		vec4(0.25, -0.25, 0.0, 1.0),
		vec4(0.0, 0.25, 0.0, 1.0) };
	glVertexAttribPointer(0,1, GL_INT,GL_TRUE,1,&vtcs);
	subMesh.vao = points;
	*/
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);

	subMesh.primitiveMode = GL_TRIANGLES;
	subMesh.renderMode = ORDERED;
	subMesh.count = 3;

	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);
}

#include "Figure3.h"
Figure3::Figure3(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void Figure3::buildMesh() {
	std::vector<pntVertexData> vertexData;
	vertexData.push_back(vec4(0.0, 0.75, 0.0, 1.0));//1

	vertexData.push_back(vec4(-0.25, 0.25, 0.0, 1.0));//2
	vertexData.push_back(vec4(0.25, 0.25, 0.0, 1.0));//3

	vertexData.push_back(vec4(-0.75, 0.0, 0.0, 1.0));//4
	vertexData.push_back(vec4(0.75, 0.0, 0.0, 1.0));//5

	vertexData.push_back(vec4(-0.25, -0.25, 0.0, 1.0));//6
	vertexData.push_back(vec4(0.25, -0.25, 0.0, 1.0));//7

	vertexData.push_back(vec4(0.0, -0.75, 0.0, 1.0));//8


	// or indexed (call glDrawElements
	// Set the render mode for either ordered (call glDrawArrays)

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(4);

	indices.push_back(5);
	indices.push_back(7);
	indices.push_back(6);

	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(5);

	indices.push_back(1);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(6);


	SubMesh subMesh = buildSubMesh(vertexData,indices);
	subMesh.primitiveMode = GL_TRIANGLES;
	// Create a material struct
	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);

}
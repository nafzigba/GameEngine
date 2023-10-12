#include "Figure1.h"
Figure1::Figure1(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void Figure1::buildMesh() {
	std::vector<pntVertexData> vertexData;

	vertexData.push_back(vec4(0.5, 0.5, 0.0, 1.0));
	vertexData.push_back(vec4(0.3, 0.0, 0.0, 1.0));
	vertexData.push_back(vec4(0.7, 0.0, 0.0, 1.0));

	vertexData.push_back(vec4(-0.2, 0.0, 0.0, 1.0));
	vertexData.push_back(vec4(0.0, -0.5, 0.0, 1.0));
	vertexData.push_back(vec4(0.2, 0.0, 0.0, 1.0));

	vertexData.push_back(vec4(-0.5, 0.5, 0.0, 1.0));
	vertexData.push_back(vec4(-0.7, 0.0, 0.0, 1.0));
	vertexData.push_back(vec4(-0.3, 0.0, 0.0, 1.0));

	// generate and bind a vertex array object

	SubMesh subMesh = buildSubMesh(vertexData);
	// set the primitive mode
	subMesh.primitiveMode = GL_TRIANGLES;
	// set the render mode for either ordered (call gldrawarrays)
	// or indexed (call gldrawelements
	// create a material struct
	// add the submesh to the vector of sub meshes
	subMeshes.push_back(subMesh);

}
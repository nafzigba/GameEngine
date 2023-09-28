#include "Figure3.h"
Figure3::Figure3(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void Figure3::buildMesh() {
	SubMesh subMesh;
	std::vector<vec4> v;
	v.push_back(vec4(0.0, 0.75, 0.0, 1.0));//1

	v.push_back(vec4(-0.25, 0.25, 0.0, 1.0));//2
	v.push_back(vec4(0.25, 0.25, 0.0, 1.0));//3

	v.push_back(vec4(-0.75, 0.0, 0.0, 1.0));//4
	v.push_back(vec4(0.75, 0.0, 0.0, 1.0));//5

	v.push_back(vec4(-0.25, -0.25, 0.0, 1.0));//6
	v.push_back(vec4(0.25, -0.25, 0.0, 1.0));//7

	v.push_back(vec4(0.0, -0.75, 0.0, 1.0));//8


	//subMesh.material.basicColor = BLUE_RGBA;
	//	// Generate and bind a vertex array object
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);
	//	// Creating a single buffer
	glGenBuffers(1, &subMesh.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, subMesh.vertexBuffer);
	//	cout << "vertex buffer = " << subMesh.vertexBufer << endl;
	//	// Buffer all the vertex data
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(vec4), &v[0], GL_STATIC_DRAW);
	//	// Describe the layout of the vertex data
	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(vec4), 0);

	//	// Turn on the flow of the vertex data
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(12, 4, GL_FLOAT, false, sizeof(pcVertexData), (const void*)sizeof(vec4));
	//glEnableVertexAttribArray(12);
	cout << "called" << endl;
	std::vector<GLuint> indices;
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



	glGenBuffers(1, &subMesh.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	subMesh.count = static_cast<GLuint>(indices.size());

	subMesh.primitiveMode = GL_TRIANGLES;

	// Set the render mode for either ordered (call glDrawArrays)
	// or indexed (call glDrawElements
	subMesh.renderMode = INDEXED;

	// Create a material struct
	subMesh.material.basicColor = Material().basicColor;
	// Add to the subMeshes that are part of the mesh component
	subMeshes.push_back(subMesh);

}
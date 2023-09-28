#include "Figure1.h"
Figure1::Figure1(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
void Figure1::buildMesh() {
	SubMesh submesh;
	std::vector<vec4> v;
	v.push_back(vec4(0.5, 0.5, 0.0, 1.0));
	v.push_back(vec4(0.3, 0.0, 0.0, 1.0));
	v.push_back(vec4(0.7, 0.0, 0.0, 1.0));
	
	v.push_back(vec4(-0.2, 0.0, 0.0, 1.0));
	v.push_back(vec4(0.0, -0.5, 0.0, 1.0));
	v.push_back(vec4(0.2, 0.0, 0.0, 1.0));
	
	v.push_back(vec4(-0.5, 0.5, 0.0, 1.0));
	v.push_back(vec4(-0.7, 0.0, 0.0, 1.0));
	v.push_back(vec4(-0.3, 0.0, 0.0, 1.0));
	// generate and bind a vertex array object
	glGenVertexArrays(1, &submesh.vao);
	glBindVertexArray(submesh.vao);
	cout << "vao = " << submesh.vao << endl;
	// creating a single buffer
	glGenBuffers(1, &submesh.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, submesh.vertexBuffer);
	cout << "vertex buffer = " << submesh.vertexBuffer << endl;
	// buffer all the vertex data
	glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(vec4), &v[0], GL_STATIC_DRAW);
	// describe the layout of the vertex data
	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(vec4), 0);
	// turn on the flow of he vertex data
	glEnableVertexAttribArray(0);
	// if we are doing indexed rendering, we would also buffer the indices
	// save the number of vertices or indices
	submesh.count = static_cast<GLuint>(v.size());
	// set the primitive mode
	submesh.primitiveMode = GL_TRIANGLES;
	// set the render mode for either ordered (call gldrawarrays)
	// or indexed (call gldrawelements
	submesh.renderMode = ORDERED;
	// create a material struct
	submesh.material.basicColor = RED_RGBA;
	// add the submesh to the vector of sub meshes
	subMeshes.push_back(submesh);

}
#include "TriangleMeshComponent.h"
TriangleMeshComponent::TriangleMeshComponent(GLuint shaderProgram, int 	updateOrder) : MeshComponent(shaderProgram, updateOrder)
{

}
/*
void TriangleMeshComponent::buildMesh()
{
	for (Triangle t : triangles) {
		buildMesh(t);
	}
}
*/
/*
void TriangleMeshComponent::orderedMesh1() {
	SubMesh submesh;
	std::vector<vec4> v;
		v.push_back(vec4(0.5, 0.5, 0.0, 1.0));
		v.push_back(vec4(0.3, 0.0, 0.0, 1.0));
		v.push_back(vec4(0.7, 0.0, 0.0, 1.0));
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
	submesh.material = Material();
	submesh.material.basicColor = BLUE_RGBA;
	// add the submesh to the vector of sub meshes
	subMeshes.push_back(submesh);
}

void TriangleMeshComponent::orderedMesh2() {
	SubMesh submesh;
	std::vector<vec4> v;
	v.push_back(vec4(0.0, 0.5, 0.0, 1.0));
	v.push_back(vec4(-0.3, 0.0, 0.0, 1.0));
	v.push_back(vec4(-0.7, 0.0, 0.0, 1.0));
	// generate and bind a vertex array object
	glGenVertexArrays(3, &submesh.vao);
	glBindVertexArray(submesh.vao);
	cout << "vao = " << submesh.vao << endl;
	// creating a single buffer
	glGenBuffers(3, &submesh.vertexBuffer);
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
	submesh.material = Material();
	submesh.material.basicColor = GREEN_RGBA;
	// add the submesh to the vector of sub meshes
	subMeshes.push_back(submesh);
}
*/

struct pcVertexData
{
	glm::vec4 m_pos;
	glm::vec4 m_color;
	pcVertexData() {}
	pcVertexData(glm::vec4 pos, glm::vec4 col)
	{
		m_pos = pos;
		m_color = col;
	}
};
void TriangleMeshComponent::buildMesh()
{
		SubMesh subMesh;
		std::vector<vec4> v;
		v.push_back(vec4(0.5, 0.5, 0.0, 1.0));
		v.push_back(vec4(0.3, 0.0, 0.0, 1.0));
		v.push_back(vec4(0.7, 0.0, 0.0, 1.0));
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
		glGenBuffers(1, &subMesh.indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh.indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
		subMesh.count = static_cast<GLuint>(indices.size());
		
		subMesh.primitiveMode = GL_TRIANGLES;
	
		// Set the render mode for either ordered (call glDrawArrays)
		// or indexed (call glDrawElements
		subMesh.renderMode = INDEXED;
	
		// Create a material struct
		subMesh.material = Material();
		// Add to the subMeshes that are part of the mesh component
		subMeshes.push_back(subMesh);
	}

/*
GLuint vao = GL_INVALID_VALUE; // ID for Vertex Array Object for the sub-mesh

	GLuint vertexBuffer = GL_INVALID_VALUE; // ID for vertex data buffer for the sub-mesh

	GLuint indexBuffer = GL_INVALID_VALUE; // ID for index buffer for the sub-mesh (if indexed rendering is used)

	GLuint count = 0; // Either the number of vertices in the mesh or the number of indices

	RENDER_MODE renderMode = INDEXED; // Render mode for the mesh. Either ORDERED or INDEXED

	GLenum primitiveMode = GL_TRIANGLES; // Primitive mode for the mesh GL_POINTS, GL_LINES, etc.

	Material material;  // Material properties used to render the object
*/
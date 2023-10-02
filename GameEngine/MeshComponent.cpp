#include "MeshComponent.h"
#include "SharedTransformations.h"

#define VERBOSE false

/** @brief	Definition of a static data member; meshComps */
//std::vector<class MeshComponent*> MeshComponent::meshComps;
std::vector<std::shared_ptr<class MeshComponent>> MeshComponent::meshComps;

MeshComponent::~MeshComponent()
{
	if (VERBOSE) cout << "MeshComponent destructor called " << endl;

	for (auto& subMesh : subMeshes) {
		
		// Delete the VAO
		glDeleteVertexArrays(1, &subMesh.vao);
		// Delete the vertex buffer
		glDeleteBuffers(1, &subMesh.vertexBuffer);

		// Delete the index buffer
		if (subMesh.renderMode == INDEXED) {
			// TODO
			glDeleteVertexArrays(1, &subMesh.indexBuffer);
		}
	}
	
} // end destructor


// Preform drawing operations. 
void MeshComponent::draw() const
{
	/*
	glm::mat4 
	ingTransformation = mat4(1.0f);
		glUniformMatrix4fv(102, 1, GL_FALSE, glm::value_ptr(modelingTransformation));
	*/
	mat4 modelingTransformation = this->owningGameObject->getModelingTransformation(); 
	//glm::mat4 modelingTransformation = mat4(1.0f);
	//glUniformMatrix4fv(102, 1, GL_FALSE, glm::value_ptr(modelingTransformation));
	SharedTransformations::setModelingMatrix(modelingTransformation);

	if (this->owningGameObject->getState() == ACTIVE) {

		// Render all subMeshes
		// TODO
		for (auto& subMesh : subMeshes) {
			// Bind vertex array object for the subMesh
			glBindVertexArray(subMesh.vao);
			
			glUniform4fv(500, 1, glm::value_ptr(subMesh.material.basicColor));

			// Trigger vertex fetch for ordered rendering 
			if (subMesh.renderMode == ORDERED) {
				glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
			}
			else {
				glDrawElements(subMesh.primitiveMode, subMesh.count, GL_UNSIGNED_INT, 0);
			}
		}
		
	}

} // end draw


void MeshComponent::addMeshComp(std::shared_ptr<MeshComponent> meshComponent)
{
	auto iter = std::find(meshComps.begin(), meshComps.end(), meshComponent);

	if (iter == meshComps.end()) {

		meshComponent->buildMesh();

		meshComps.emplace_back(meshComponent);
		std::sort(meshComps.begin(), meshComps.end(), Component::CompareUpdateOrder);
	}

} // end addMeshComp

void MeshComponent::removeMeshComp(std::shared_ptr<MeshComponent> meshComponent)
{
	auto iter = std::find(meshComps.begin(), meshComps.end(), meshComponent);

	if (iter != meshComps.end()) {

		if (VERBOSE) cout << "removeMeshComp" << endl;

		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, meshComps.end() - 1);
		meshComps.pop_back();
	}

} // end removeMeshComp

SubMesh  MeshComponent::buildSubMesh(const std::vector<pntVertexData>& vertexData)
{

	// Create the SubMesh to be configured for the vertex data
	SubMesh subMesh;

	// Generate, bind, and load the vertex array object.
	// Store the identifier for the vertex array object in the subMesh
	// TODO
	glGenVertexArrays(1, &subMesh.vao);
	glBindVertexArray(subMesh.vao);

	// Create a buffer and load the vertex positions and colors into it.
	// Store the identifier for the buffer in the subMesh.
	// TODO
	glGenBuffers(1, &subMesh.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, subMesh.vertexBuffer);

	// Specify the location and data format of an array of vertex 
	// positions
	// TODO

	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(pntVertexData)
		, &vertexData[0], GL_STATIC_DRAW);


	// Enable the flow of vertex positions into the vertex shader
	// TODO
	glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(pntVertexData) , 0);
	glEnableVertexAttribArray(0);
	// Store the number of vertices to be rendered in the subMesh
	// TODO
	subMesh.count = static_cast<GLuint>(vertexData.size());

	// Store the renderMode in the subMesh for ORDERED rendering
	// TODO
	subMesh.renderMode = ORDERED;

	return subMesh;

} // end buildSubMesh

SubMesh  MeshComponent::buildSubMesh(const std::vector<pntVertexData>& vertexData, const std::vector<unsigned int>& indices)
{

	// Create the SubMesh to be configured for the vertex data
	SubMesh subMesh = buildSubMesh(vertexData);

	subMesh.count = static_cast<GLuint>(vertexData.size());

	glGenBuffers(1, &subMesh.indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh.indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
	subMesh.count = static_cast<GLuint>(indices.size());

	// Store the renderMode in the subMesh for ORDERED rendering
	// TODO
	subMesh.renderMode = INDEXED;

	return subMesh;

} // end buildSubMesh




const std::vector<std::shared_ptr<MeshComponent>> & MeshComponent::GetMeshComponents()
{
	return meshComps;

}


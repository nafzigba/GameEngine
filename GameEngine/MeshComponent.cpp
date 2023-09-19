#include "MeshComponent.h"

#define VERBOSE false

/** @brief	Definition of a static data member; meshComps */
//std::vector<class MeshComponent*> MeshComponent::meshComps;
std::vector<std::shared_ptr<class MeshComponent>> MeshComponent::meshComps;

MeshComponent::~MeshComponent()
{
	if (VERBOSE) cout << "MeshComponent destructor called " << endl;

	for (auto& subMesh : subMeshes) {
		
		// Delete the VAO
		// TODO

		// Delete the vertex buffer
		// TODO

		// Delete the index buffer
		if (subMesh.renderMode == INDEXED) {
			// TODO
		}
	}
	
} // end destructor


// Preform drawing operations. 
void MeshComponent::draw() const
{
	if (this->owningGameObject->getState() == ACTIVE) {

		// Render all subMeshes
		// TODO
		glUseProgram(shaderProgram);
		for (auto& subMesh : subMeshes) {

			// Bind vertex array object for the subMesh
			glBindVertexArray(subMesh.vao);

			// Trigger vertex fetch for ordered rendering 
			glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
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



const std::vector<std::shared_ptr<MeshComponent>> & MeshComponent::GetMeshComponents()
{
	return meshComps;

}


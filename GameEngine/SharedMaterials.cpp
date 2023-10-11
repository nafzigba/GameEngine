#include "SharedMaterials.h"


std::vector<GLint> SharedMaterials::matLocations;
Material SharedMaterials::material;

GLuint SharedMaterials::normalLightLocation; // Byte offset of the modeling matrix to transform normal vectors

GLuint SharedMaterials::lightPositionLocation;  // Byte offset of the eye position

SharedUniformBlock SharedMaterials::matColorBlock(matColorBlockBindingPoint);
SharedUniformBlock SharedMaterials::lightBlock(lightBlockBindingPoint);

const std::string SharedMaterials::materialBlockName = "materialBlock";

const std::string SharedMaterials::lightBlockName = "lightBlock";

void SharedMaterials::setUniformBlockForShader(GLuint shaderProgram)
{
	std::vector<std::string> matMemberNames = { "basicColor", "ambientColor", "diffuseMat", "specMat", "emMat"};

	matLocations = matColorBlock.setUniformBlockForShader(shaderProgram, materialBlockName, matMemberNames);

	// Save locations
	

	//normalLightLocation = uniformOffsets[1];

	uniformOffsets.clear();
	std::vector<std::string> lightBlockNames = { "worldEyePosition" };

	uniformOffsets = lightBlock.setUniformBlockForShader(shaderProgram, lightBlockName, lightBlockNames);

	// Save location
	lightPositionLocation = uniformOffsets[0];

} // end setUniformBlockForShader


void SharedMaterials::setMaterial(Material m) {
	if (matColorBlock.getSize() > 0) {
		glBindBuffer(GL_UNIFORM_BUFFER, matColorBlock.getBuffer());
		SharedMaterials::material = m;
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[0], sizeof(vec4), glm::value_ptr(material.ambientMat));
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[1], sizeof(vec4), &material);
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[2], sizeof(vec4), &material);
		glBufferSubData(GL_UNIFORM_BUFFER, matLocation, sizeof(vec4), &material);
		glBufferSubData(GL_UNIFORM_BUFFER, matLocation, sizeof(vec4), &material);
		glBufferSubData(GL_UNIFORM_BUFFER, matLocation, sizeof(float), &material);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
} 

// end setProjectionMatrix

/*
// Accessor for the current projection matrix
glm::vec4 SharedMaterials::getBasicColor()
{
	return basicColor;

} // end getProjectionMatrix


void SharedMaterials::setDiffuseMat(glm::vec4 modelingMatrix)
{
	if (matColorBlock.getSize() > 0) {

		// Bind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, matColorBlock.getBuffer());

		SharedMaterials::modelMatrix = modelingMatrix;

		glBufferSubData(GL_UNIFORM_BUFFER,diffuseLocation, sizeof(glm::vec4), glm::value_ptr(modelMatrix));

		// Create a modeling transform for normals that will be correct under non-uniform scale
		vec4 normalModelMatrix = glm::transpose(glm::inverse(modelMatrix));

		glBufferSubData(GL_UNIFORM_BUFFER, normalLightLocation, sizeof(glm::vec4), glm::value_ptr(normalModelMatrix));

		// Unbind the buffer. 
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

} // end setModelingMatrix


// Accessor for the current modeling matrix
glm::vec4 SharedMaterials::getDiffuseMat()
{
	return diffuseMat;

} // end getModelingMatrix


*/



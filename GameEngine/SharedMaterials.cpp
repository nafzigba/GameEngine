#include "SharedMaterials.h"


std::vector<GLint> SharedMaterials::matLocations;
Material SharedMaterials::material;

GLuint SharedMaterials::normalLightLocation; // Byte offset of the modeling matrix to transform normal vectors


std::vector<GLint> SharedMaterials::lightPositionLocations;  // Byte offset of the eye position

SharedUniformBlock SharedMaterials::matColorBlock(matColorBlockBindingPoint);
SharedUniformBlock SharedMaterials::lightBlock(lightBlockBindingPoint);

const std::string SharedMaterials::materialBlockName = "materialBlock";

const std::string SharedMaterials::lightBlockName = "lightBlock";

void SharedMaterials::setUniformBlockForShader(GLuint shaderProgram)
{
	std::vector<std::string> matMemberNames = {"ambientColor", "diffuseMat", "specularMat", "emmissiveMat", "specularExp"};
	//std::vector<std::string> matMemberNames = {"obj"};

	matLocations = matColorBlock.setUniformBlockForShader(shaderProgram, materialBlockName, matMemberNames);

	std::vector<std::string> lightBlockNames = { "ambientColor", "diffuseColor", "specularColor", "posLight", "dirLight"};

	lightPositionLocations = lightBlock.setUniformBlockForShader(shaderProgram, lightBlockName, lightBlockNames);

	// Save location

} // end setUniformBlockForShader


void SharedMaterials::setMaterial(Material m) {
	if (matColorBlock.getSize() > 0) {
		glBindBuffer(GL_UNIFORM_BUFFER, matColorBlock.getBuffer());
		material = m;
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[0], sizeof(vec4), glm::value_ptr(material.ambientMat));
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[1], sizeof(vec4), glm::value_ptr(material.diffuseMat));
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[2], sizeof(vec4), glm::value_ptr(material.specularMat));
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[3], sizeof(vec4), glm::value_ptr(material.emmissiveMat));
		glBufferSubData(GL_UNIFORM_BUFFER, matLocations[4], sizeof(float), &material.specularExp);
	}
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
} 
void SharedMaterials::setLight(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor, vec4 posLight, vec4 dirLight) {
	if (lightBlock.getSize() > 0) {
		glBindBuffer(GL_UNIFORM_BUFFER, lightBlock.getBuffer());
		glBufferSubData(GL_UNIFORM_BUFFER, lightPositionLocations[0], sizeof(vec4), glm::value_ptr(ambientColor));
		glBufferSubData(GL_UNIFORM_BUFFER, lightPositionLocations[1], sizeof(vec4), glm::value_ptr(diffuseColor));
		glBufferSubData(GL_UNIFORM_BUFFER, lightPositionLocations[2], sizeof(vec4), glm::value_ptr(specularColor));
		glBufferSubData(GL_UNIFORM_BUFFER, lightPositionLocations[3], sizeof(vec4), glm::value_ptr(posLight));
		glBufferSubData(GL_UNIFORM_BUFFER, lightPositionLocations[4], sizeof(vec4), glm::value_ptr(dirLight));
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



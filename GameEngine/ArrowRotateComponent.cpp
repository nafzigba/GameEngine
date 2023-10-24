#include "ArrowRotateComponent.h"

ArrowRotateComponent::ArrowRotateComponent(float rotRateDegPS, int updateOrder) 
	:Component(updateOrder), radianRotRate(glm::radians(rotRateDegPS)) {

}

void ArrowRotateComponent::update(const float& deltaTime) {
	mat4 rot = owningGameObject->getRotation();
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT)) {
		rot *= glm::rotate(radianRotRate * deltaTime, UNIT_Y_V3);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT)) {
		rot *= glm::rotate(-radianRotRate * deltaTime, UNIT_Y_V3);
	}
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP)) {
		rot *= glm::rotate(-radianRotRate * deltaTime, UNIT_X_V3);
	}
	else if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN)) {
		rot *= glm::rotate(radianRotRate * deltaTime, UNIT_X_V3);
	}
	this->owningGameObject->setRotation(rot);

}
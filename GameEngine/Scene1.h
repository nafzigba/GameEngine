#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h" 
#include "TriangleMeshComponent.h"
#include "Figure1.h"
#include "Figure2.h"
#include "Figure3.h"


class Scene1 : public Game
{

	void loadScene()
	{
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "shader/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "shader/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		GLuint shaderProgram = BuildShaderProgram(shaders);


		MeshComponentPtr triangle = std::make_shared<TriangleMeshComponent>(shaderProgram, 500);
		MeshComponentPtr fig1 = std::make_shared<Figure1>(shaderProgram, 1);
		MeshComponentPtr fig2 = std::make_shared<Figure2>(shaderProgram, 2);
		MeshComponentPtr fig3 = std::make_shared<Figure3>(shaderProgram, 3);

		glUseProgram(shaderProgram);

		//triangle->buildMesh();
		gameObject = std::make_shared<GameObject>();
		gameObject1 = std::make_shared<GameObject>();
		gameObject2 = std::make_shared<GameObject>();
		gameObject3 = std::make_shared<GameObject>();

		MeshComponent::addMeshComp(triangle);
		MeshComponent::addMeshComp(fig1);
		MeshComponent::addMeshComp(fig2);
		MeshComponent::addMeshComp(fig3);

		gameObject->addComponent(triangle);
		this->gameObject->setState(PAUSED);
		gameObject1->addComponent(fig1);
		this->gameObject1->setState(PAUSED);
		gameObject2->addComponent(fig2);
		this->gameObject2->setState(PAUSED);
		gameObject3->addComponent(fig3);
		this->gameObject3->setState(PAUSED);

		this->addChildGameObject(gameObject);
		this->addChildGameObject(gameObject1);
		this->addChildGameObject(gameObject2);
		this->addChildGameObject(gameObject3);


	} // end loadScene
	virtual void processGameInput()
	{
		Game::processGameInput();
		//tri
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0) && GLFW_PRESS) {
			zero_keyDown = !zero_keyDown;
			if (zero_keyDown) {
				this->gameObject->setState(this->gameObject->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		//fig1
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1) && GLFW_PRESS) {
			zero_keyDown = !zero_keyDown;
			if (zero_keyDown) {
				this->gameObject1->setState(this->gameObject1->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		//fig2
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2) && GLFW_PRESS) {
			zero_keyDown = !zero_keyDown;
			if (zero_keyDown) {
				this->gameObject2->setState(this->gameObject2->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		//fig3
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3) && GLFW_PRESS) {
			zero_keyDown = !zero_keyDown;
			if (zero_keyDown) {
				this->gameObject3->setState(this->gameObject3->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
	}

protected:
	std::shared_ptr<GameObject> gameObject;
	std::shared_ptr<GameObject> gameObject1;
	std::shared_ptr<GameObject> gameObject2;
	std::shared_ptr<GameObject> gameObject3;
	bool zero_keyDown = false;
	bool one = false;
	bool two_keyDown = false;
	bool three_keyDown = false;

};
/*


	for (auto& subMesh : subMeshes) {
		if (subMesh.renderMode == ORDERED) {
			glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
		}
		else {
			glDrawElements(subMesh.primitiveMode, subMesh.count, GL_UNSIGNED_INT, 0);
		}
	}


*/
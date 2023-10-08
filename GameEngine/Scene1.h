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
		/*
		ShaderInfo shaders[] = {
			{ GL_VERTEX_SHADER, "shader/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "shader/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		GLuint shaderProgram = BuildShaderProgram(shaders);
		SharedTransformations::setUniformBlockForShader(shaderProgram);

		Material sphereMat;
		//sphereMat.basicColor = vec4(0.5f,0.6f,1.0f,1.0f);


		MeshComponentPtr triangle = std::make_shared<TriangleMeshComponent>(shaderProgram, 500);
		MeshComponentPtr fig1 = std::make_shared<Figure1>(shaderProgram, 1);
		MeshComponentPtr fig2 = std::make_shared<Figure2>(shaderProgram, 2);
		MeshComponentPtr fig3 = std::make_shared<Figure3>(shaderProgram, 3);
		MeshComponentPtr figS = std::make_shared<SphereMeshComponent>(shaderProgram, sphereMat, 0.5f, 1.0f,12,16,100,-1.0f,.05f);
		MeshComponentPtr figS2 = std::make_shared<SphereMeshComponent>(shaderProgram, sphereMat, 0.5f, 1.0f, 12, 16, 100, 1.0f, .05f);

		glUseProgram(shaderProgram);

		//triangle->buildMesh();
		gameObject = std::make_shared<GameObject>();
		gameObject1 = std::make_shared<GameObject>();
		gameObject2 = std::make_shared<GameObject>();
		gameObject3 = std::make_shared<GameObject>();
		sphere = std::make_shared<GameObject>();
		sphere2 = std::make_shared<GameObject>();

		MeshComponent::addMeshComp(triangle);
		MeshComponent::addMeshComp(fig1);
		MeshComponent::addMeshComp(fig2);
		MeshComponent::addMeshComp(fig3);
		MeshComponent::addMeshComp(figS);
		MeshComponent::addMeshComp(figS2);

		gameObject->addComponent(triangle);
		this->gameObject->setState(PAUSED);
		gameObject1->addComponent(fig1);
		this->gameObject1->setState(PAUSED);
		gameObject2->addComponent(fig2);
		this->gameObject2->setState(PAUSED);
		gameObject3->addComponent(fig3);
		this->gameObject3->setState(PAUSED);
		sphere->addComponent(figS);
		this->sphere->setState(PAUSED);
		sphere2->addComponent(figS2);
		this->sphere2->setState(PAUSED);

		this->addChildGameObject(gameObject);
		this->addChildGameObject(gameObject1);
		this->addChildGameObject(gameObject2);
		this->addChildGameObject(gameObject3);
		this->addChildGameObject(sphere);
		this->addChildGameObject(sphere2);
		*/

	} // end loadScene
	virtual void processGameInput()
	{
		Game::processGameInput();
		//tri
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0) && zero_keyDown == false) {
			zero_keyDown = true;
			if (zero_keyDown) {
				this->gameObject->setState(this->gameObject->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_0)) {
			zero_keyDown = false;
		}
		//fig1
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1) && one == false) {
			one = true;
			if (one) {
				this->gameObject1->setState(this->gameObject1->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_1)) {
			one = false;
		}
		//fig2
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2) && two_keyDown == false) {
			two_keyDown = true;
			if (two_keyDown) {
				this->gameObject2->setState(this->gameObject2->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_2)) {
			two_keyDown = false;
		}
		//fig3
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3) && three_keyDown == false) {
			three_keyDown = true;
			if (three_keyDown) {
				this->gameObject3->setState(this->gameObject3->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_3)) {
			three_keyDown = false;
		}
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) && s_keyDown == false) {
			s_keyDown = true;
			if (s_keyDown) {
				this->sphere->setState(this->sphere->getState() == ACTIVE ? PAUSED : ACTIVE);
				this->sphere2->setState(this->sphere->getState() == ACTIVE ? PAUSED : ACTIVE);
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S)) {
			s_keyDown = false;
		}
	}

protected:
	std::shared_ptr<GameObject> gameObject;
	std::shared_ptr<GameObject> gameObject1;
	std::shared_ptr<GameObject> gameObject2;
	std::shared_ptr<GameObject> gameObject3;
	std::shared_ptr<GameObject> sphere;
	std::shared_ptr<GameObject> sphere2;
	bool zero_keyDown = false;
	bool one = false;
	bool two_keyDown = false;
	bool three_keyDown = false;
	bool s_keyDown = false;
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
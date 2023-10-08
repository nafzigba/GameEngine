#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h"


class Proj1Scene : public Game
{
	void loadScene()
	{
		ShaderInfo shaders1[] = {
			{ GL_VERTEX_SHADER, "shader/vertexShader.glsl" },
			{ GL_FRAGMENT_SHADER, "shader/fragmentShader.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		ShaderInfo shaders2[] = {
			{ GL_VERTEX_SHADER, "shader/vertexShader1.glsl" },
			{ GL_FRAGMENT_SHADER, "shader/fragmentShader1.glsl" },
			{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		GLuint shaderProgram1 = BuildShaderProgram(shaders1);
		GLuint shaderProgram2 = BuildShaderProgram(shaders2);
		SharedTransformations::setUniformBlockForShader(shaderProgram1);
		SharedTransformations::setUniformBlockForShader(shaderProgram2);
		vector<string> matBlockItems;
		string name = "MaterialBlock";
		matBlockItems.push_back("Material");
		//SharedUniformBlock s;
		//std::vector<GLint> layouts = SharedUniformBlock::setUniformBlockForShader(shaderProgram1,name, matBlockItems);

		//glUseProgram(shaderProgram2);
		cout << "here" << endl;

		vector<MeshComponentPtr> figs;
		Material sphereMat;
		sphereMat.basicColor = vec4(0.5f, 0.6f, 1.0f, 1.0f);
		for (int i = 1; i < 5; i++) {
			//MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.5f);
			MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.25f,2*i+2,3*i+3,i);
			glUseProgram(shaderProgram1);
			std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();;
			MeshComponent::addMeshComp(fig);
			gameObject->addComponent(fig);
			gameObject->setState(PAUSED);

			gameObject->setPosition(vec3(.75f*i - 2.0f,.50f, 0.0f),LOCAL);

			spheres.push_back(gameObject);
			this->addChildGameObject(gameObject);
		}
		
		for (int i = 1; i < 5; i++) {
			//MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.5f);
			MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.25f, 3 * i + 3, 4 * i + 4, i);
			glUseProgram(shaderProgram1);
			std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();;
			MeshComponent::addMeshComp(fig);
			gameObject->addComponent(fig);
			gameObject->setState(PAUSED);

			gameObject->setPosition(vec3(.75f * i - 2.0f, -.50f, 0.0f), LOCAL);

			spheres.push_back(gameObject);
			this->addChildGameObject(gameObject);
		}

	}
	virtual void processGameInput()
	{
		Game::processGameInput();
		
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) && s_keyDown == false) {
			s_keyDown = true;
			if (s_keyDown) {
				for (std::shared_ptr<GameObject> s : spheres) {
					s->setState(s->getState() == ACTIVE ? PAUSED : ACTIVE);
					//this->sphere2->setState(this->sphere->getState() == ACTIVE ? PAUSED : ACTIVE);

				}
			}
		}
		else if (!glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S)) {
			s_keyDown = false;
		}
	}

protected:
	vector<std::shared_ptr<GameObject>> spheres;
	bool s_keyDown = false;
};
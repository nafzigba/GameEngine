#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h"
#include "SharedMaterials.h"

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
		SharedMaterials::setUniformBlockForShader(shaderProgram1);
		SharedMaterials::setUniformBlockForShader(shaderProgram2);


		Material sphereMat;
		sphereMat.ambientMat = vec4(0.10f, 1.0f, .10f, 1.0f);
		sphereMat.diffuseMat = vec4(0.10f, 1.0f, .10f, 1.0f);
		sphereMat.specularMat = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		sphereMat.emmissiveMat = vec4(0.1f, 0.1f, 0.1f, 1.0f);
		sphereMat.specularExp = 256;

		vec4 ambientColor(0.10f,0.10f,0.10f,1.0f);
		vec4 diffuseColor(0.10f, 0.10f, 0.10f, 1.0f);
		vec4 specularColor(1.0f, 1.0f, 1.0f, 1.0f);
		vec4 posLight(50.0f, 50.0f, -50.0f, 1.0f);
		vec4 dirLight(-1.0f, -1.0f, 11.0f, 1.0f);
		SharedMaterials::setLight(ambientColor,diffuseColor,specularColor,posLight,dirLight);

		cout << "here" << endl;
		vector<MeshComponentPtr> figs;
		
		for (int i = 1; i < 5; i++) {
			//MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.5f);
			MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.25f,2*i+1,3*i+1,i);
			glUseProgram(shaderProgram1);
			std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
			MeshComponent::addMeshComp(fig);
			gameObject->addComponent(fig);
			gameObject->setState(ACTIVE);

			gameObject->setPosition(vec3(.75f*i - 2.0f,.50f, 0.0f),LOCAL);

			spheres.push_back(gameObject);
			this->addChildGameObject(gameObject);
		}
		
		Material sphereMat2;
		sphereMat2.ambientMat = vec4(0.75f, 0.2f, 0.250f, 1.0f);
		sphereMat2.diffuseMat = vec4(0.75f, 0.2f, 0.250f, 1.0f);
		sphereMat2.specularMat = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		sphereMat2.emmissiveMat = vec4(0.15f, 0.16f, .10f, 1.0f);
		sphereMat2.specularExp = 256;
		SharedMaterials::setLight(ambientColor, diffuseColor, specularColor, posLight, dirLight);

		for (int i = 1; i < 5; i++) {
			//MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram1, sphereMat, 0.5f);
			MeshComponentPtr fig = std::make_shared<SphereMeshComponent>(shaderProgram2, sphereMat2, 0.25f, 2 * i + 1, 3 * i + 1, i);
			glUseProgram(shaderProgram1);
			std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>();
			MeshComponent::addMeshComp(fig);
			gameObject->addComponent(fig);
			gameObject->setState(ACTIVE);

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
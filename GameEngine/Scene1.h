#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h"



class Scene1 : public Game
{
	GLuint shaderProgram;
	SubMesh subMesh;
	std::vector<SubMesh> subMeshes;
	void loadScene() override
	{
		ShaderInfo shaders[] = {
	{ GL_VERTEX_SHADER, "shader/vertexShader.glsl" },
	{ GL_FRAGMENT_SHADER, "shader/fragmentShader.glsl" },
	{ GL_NONE, NULL } // signals that there are no more shaders 
		};
		this->shaderProgram = BuildShaderProgram(shaders);
		
		glUseProgram(shaderProgram);
		


		glGenVertexArrays(1, &subMesh.vao);
		glBindVertexArray(subMesh.vao);

		subMesh.count = 3;
		subMesh.primitiveMode = GL_TRIANGLES;
		subMesh.renderMode = ORDERED;

		subMeshes.push_back(subMesh);

		//subMesh.material = Material();

		//initialize ptr of obj
		GameObjectPtr gameObject =
			std::make_shared<GameObject>();
		//make myObj
		ComponentPtr myComponent =
			std::make_shared<BradleyComponent>();
		//add obj to ptr
		//gameObject->addComponent(myComponent);
		//add objs to game
		//this->addChildGameObject(gameObject);


	} // end loadScene
	void renderScene() override {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render loop
		// 
		for (auto& subMesh : subMeshes) {
			if (subMesh.renderMode == ORDERED) {
				glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
			}
			else {
				glDrawElements(subMesh.primitiveMode, subMesh.count, GL_UNSIGNED_INT, 0);
			}
		}

		//glDrawArrays(subMesh.primitiveMode, 0, subMesh.count);
		

		// Swap the front and back buffers
		glfwSwapBuffers(renderWindow);
	}
	
};

#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h" 
#include "TriangleMeshComponent.h"
#include "TriangleMeshComponent1.h"
#include "TriangleMeshComponent2.h"


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
		glUseProgram(shaderProgram);

		MeshComponentPtr triangle = std::make_shared<TriangleMeshComponent>(shaderProgram,1);
		//triangle->buildMesh();
		gameObject = std::make_shared<GameObject>();
		gameObject1 = std::make_shared<GameObject>();
		gameObject2 = std::make_shared<GameObject>();

		MeshComponent::addMeshComp(triangle);

		gameObject->addComponent(triangle);


		//subMesh.material = Material();

		//initialize ptr of obj
		//make myObj
		//ComponentPtr myComponent = std::make_shared<BradleyComponent>();
		//add obj to ptr
		//gameObject->addComponent(myComponent);
		//add objs to game
		this->addChildGameObject(gameObject);
		this->addChildGameObject(gameObject1);


	} // end loadScene
	virtual void processGameInput()
	{
		Game::processGameInput();

	}

protected:
	std::shared_ptr<GameObject> gameObject;
	std::shared_ptr<GameObject> gameObject1;
	std::shared_ptr<GameObject> gameObject2;
	bool zero_keyDown = false;
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
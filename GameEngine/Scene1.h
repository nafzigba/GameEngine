#pragma once
#include "GameEngine.h"
#include "BuildShaderProgram.h"
#include "TriangleMeshComponent.h"


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
		

		MeshComponentPtr triangle = std::make_shared<TriangleMeshComponent>(shaderProgram,500);
		GameObjectPtr gameObject = std::make_shared<GameObject>();

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


	} // end loadScene
	
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
#pragma once
#include <string>
#include <unordered_map>

#include "MathLibsConstsFuncs.h"
#include "Component.h"
#include "Material.h"
#include "Bullet/btBulletDynamicsCommon.h"

using namespace constants_and_types;


/**
 * @struct	pntVertexData
 *
 * @brief	Structure for holding vertex data (position, normal, and texture
 * 			coordinate for a single vertex.
 */
struct pntVertexData
{
	// Position of the vertex in Object coordinates
	glm::vec4 m_pos;

	// Normal vector for the vertex in Object coordinates
	glm::vec3 m_normal;

	// 2D vertex texture coordinate
	glm::vec2 m_textCoord;

	pntVertexData(glm::vec4 pos = ZERO_V4, glm::vec3 normal = ZERO_V3,
		glm::vec2 textCoord = ZERO_V2)
	{
		m_pos = pos;
		m_normal = normal;
		m_textCoord = textCoord;
	}
};

/**
 * @enum	RENDER_MODE
 *
 * @brief	Values that represent render modes to be used when a sub-mesh if rendered.
 */
enum RENDER_MODE { ORDERED, INDEXED };

/**
 * @struct	SubMesh
 *
 * @brief	stuct containing values needed to render a sub-mesh. All visible objects
 * 			(Meshes) are rendered using one or more sub-meshes.
 */
struct SubMesh {

	GLuint vao = GL_INVALID_VALUE; // ID for Vertex Array Object for the sub-mesh

	GLuint vertexBuffer = GL_INVALID_VALUE; // ID for vertex data buffer for the sub-mesh

	GLuint indexBuffer = GL_INVALID_VALUE; // ID for index buffer for the sub-mesh (if indexed rendering is used)

	GLuint count = 0; // Either the number of vertices in the mesh or the number of indices

	RENDER_MODE renderMode = INDEXED; // Render mode for the mesh. Either ORDERED or INDEXED

	GLenum primitiveMode = GL_TRIANGLES; // Primitive mode for the mesh GL_POINTS, GL_LINES, etc.

	Material material;  // Material properties used to render the object

}; // end SubMesh



/**
 * @class	Mesh
 *
 * @brief	Base class for all objects that will appear visually in the scene. All meshes
 * 			are rendered using one or more sub-meshes.
 */
class MeshComponent : public Component
{
public: 

	/**
	 * @fn	MeshComponent::MeshComponent(GLuint shaderProgram, int updateOrder = 100)
	 *
	 * @brief	Constructor
	 *
	 * @param 	shaderProgram	Shader program that will be used to render the
	 * 							mesh.
	 * @param 	updateOrder  	(Optional) The update order of the component.
	 */
	MeshComponent(GLuint shaderProgram, int updateOrder = 100)
		: shaderProgram(shaderProgram), Component(updateOrder)
	{
		componentType = MESH;
	};

	/**
	 * @fn	MeshComponent::virtual~MeshComponent();
	 *
	 * @brief	Destructor. Deletes all dynamically allocated data.
	 */
	virtual~MeshComponent();

	/**
	 * @fn	virtual void MeshComponent::buildMesh() = 0;
	 *
	 * @brief	Buffers all the data that is associated with the vertex data for
	 * 			this object. Creates a Vertex Array Object that holds references
	 * 			to the vertex buffers, the index buffer and the layout
	 * 			specification. This is a pure virtual method and must be
	 * 			overridden.
	 */
	virtual void buildMesh()=0;



	/**
	 * @fn	virtual void MeshComponent::draw() const;
	 *
	 * @brief	Renders all sub-meshes that are part of the object. Binds the
	 * 			vertex array object, sets the material properties, and sets the
	 * 			modeling transformation based on the world transformation of the
	 * 			owning game object.
	 */
	virtual void draw() const;

	/**
	 * @fn	static void MeshComponent::addMeshComp(std::shared_ptr<class MeshComponent> meshComponent);
	 *
	 * @brief	Adds a mesh component to the Game
	 *
	 * @param 	meshComponent	If non-null, the mesh.
	 */
	static void addMeshComp(std::shared_ptr<class MeshComponent> meshComponent);

	/**
	 * @fn	static void MeshComponent::removeMeshComp(std::shared_ptr<class MeshComponent> meshComponent);
	 *
	 * @brief	Removes the mesh component from the Game
	 *
	 * @param 	meshComponent	If non-null, the mesh.
	 */
	static void removeMeshComp(std::shared_ptr<class MeshComponent> meshComponent);

	/**
	 * @fn	static const std::vector<std::shared_ptr<class MeshComponent>> MeshComponent::GetMeshComponents();
	 *
	 * @brief	Gets mesh components
	 *
	 * @returns	Null if it fails, else the vector containing all mesh components
	 * 			that should be rendered.
	 */
	static const std::vector<std::shared_ptr<class MeshComponent>> & GetMeshComponents();

protected:

	/**
 * @fn	SubMesh MeshComponent::buildSubMesh(
 *					const std::vector<pntVertexData>& vertexData);
 *
 * @brief	Builds one sub mesh that will be rendered using sequential
 * 		rendering based the vertex data that are passed to it. The
 *	 		vertex data is loaded into a buffer located in GPU memory.
 *
 * @param 	vertexData	Information describing the vertex.
 *
 * @returns	A SubMesh to be added to the subMeshese vector.
 */
	SubMesh buildSubMesh(const std::vector<pntVertexData>& vertexData);
	/**
 * @fn	SubMesh MeshComponent::buildSubMesh(
 *					const std::vector<pntVertexData>& vertexData,
 *					const std::vector<unsigned int>& indices);
 *
 * @brief	Builds one sub mesh  that will be rendered using indexed
 *			rendering based the vertex data, indices, and material
 *			properties that are passed to it. Both the vertex data and
 * 		the indices are loaded into buffers located in GPU memory.
 *
 * @param 	vertexData	Information describing the vertex.
 * @param 	indices   	indices for indexed rendering.
 *
 * @returns	A SubMesh.
 */
	SubMesh buildSubMesh(const std::vector<pntVertexData>& vertexData,
		const std::vector<unsigned int>& indices);


	/** @brief	Indentifier for the shader program used to render all sub-meshes */
	GLuint shaderProgram = 0; 

	/** @brief	Container for all sub meshes that are part of this component.*/
	std::vector<SubMesh> subMeshes;

	/** @brief	All mesh components that need to be rendered. */
	static std::vector<std::shared_ptr<class MeshComponent>> meshComps;

}; // end MeshComponent class





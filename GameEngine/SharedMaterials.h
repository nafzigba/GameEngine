#ifndef _SHARED_MATERIAL_H_
#define	_SHARED_MATERIAL_H_

#include "SharedUniformBlock.h"
#include "Material.h"

#define matColorBlockBindingPoint 5
#define lightBlockBindingPoint 6

/**

A static class that supports working with the two uniform blocks shown below.

setUniformBlockForShader should be called for every shader program that includes
the uniform block below. This will create a buffers for each uniform block
and bind the buffers and uniform blocks together through the binding points.
Binding points for the two blocks and the associated buffers are defined above.

Adding a #include for this header file makes the functionality avaible through
the class name.

layout(shared) uniform transformBlock
{
	mat4 modelMatrix;
	mat3 normalModelMatrix;
	mat4 viewingMatrix;
	mat4 projectionMatrix;
};

layout (shared) uniform worldEyeBlock
{
	vec3 worldEyePosition;
};

*/
class SharedMaterials
{
public:

	// Should be called for each shader program that includes the
	// projectionViewBlock and worldEyeBlock uniform blocks.
	static void setUniformBlockForShader(GLuint shaderProgram);

	static void setMaterial(Material m);

	static Material getMaterial();

	static void setLight(vec4 ambientColor, vec4 diffuseColor, vec4 specularColor, vec4 posLight, vec4 dirLight);



protected:

	static std::vector<GLint> matLocations;
	static Material material;

	static GLuint normalLightLocation; // Byte offset of the modeling matrix to transform normal vectors

	static GLuint lightPositionLocation;

	  // Byte offset of the eye position
	static std::vector<GLint> lightPositionLocations;

	static const std::string materialBlockName;

	static const std::string lightBlockName;


	static SharedUniformBlock matColorBlock;

	static SharedUniformBlock lightBlock;


}; // end SharedProjectionAndViewing class

#endif //_SHARED_MATERIAL_H_
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, float lengthX, float lengthY, Color color);
	static Mesh* GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ, Color color);
	static Mesh* GenerateEllipse(const std::string &meshName, float lengthX, float lengthY, Color color, unsigned numSlices = 36);
	static Mesh* GenerateCylinder(const std::string &meshName, float lengthX, float lengthZ, float height, Color color, float lengthX2 = 0, float lengthZ2 = 0, unsigned numSlices = 36);
	static Mesh* GenerateCone(const std::string &meshName, float lengthX, float lengthZ, float height, Color color, unsigned numSlices = 36);
	static Mesh* GenerateRing(const std::string &meshName, float lengthX, float lengthY, float innerR, float outerR, float angle = 360);
	static Mesh* GenerateTorus(const std::string &meshName, float innerR, float outerR, float lengthX, float lengthY, float lengthZ, Color color, unsigned stack = 18, unsigned slice = 36);
	static Mesh* GenerateSphere(const std::string &meshName, float lengthX, float lengthY, float lengthZ, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	static Mesh* GenerateSphere2(const std::string &meshName, float lengthX, float lengthY, float lengthZ, Color color, unsigned numStacks = 18, unsigned numSlices = 36);
	static Mesh* GenerateHemisphere(const std::string &meshName, float lengthX, float lengthY, float lengthZ, Color color, bool isHollow = false);
};

#endif
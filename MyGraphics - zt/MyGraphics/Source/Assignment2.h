#ifndef ASSIGNMENT_2_H
#define ASSIGNMENT_2_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

#include <vector>

using std::vector;

class Assignment2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES = 0,
		GEO_QUAD,
		GEO_CUBE,
		GEO_ELLIPSE,
		GEO_TORUS,
		GEO_SPHERE,
		GEO_HEMISPHERE,
		GEO_RING,
		GEO_LIGHTBALL,
		GEO_CYLINDER,
		GEO_CONE,

		GEO_TREE_LEAVES,
		GEO_TREE_TRUNK,

		GEO_HEAD_CORE,
		GEO_HEAD_EYES1,
		GEO_HEAD_EYES2,
		GEO_HEAD_NOSE,
		GEO_HELMET_CORE,
		GEO_HELMET_EARS,
		GEO_HELMET_EARS2,
		GEO_BODY_UPPER,
		GEO_BODY_LOWER,
		GEO_SHOULDER,
		GEO_ARM_UPPER,
		GEO_ARM_CANNON_CORE,
		GEO_ARM_CANNON_TIP,
		GEO_LEG_UPPER,
		GEO_LEG_JOINT,
		GEO_LEG_LOWER,
		GEO_LEG_FOOT,

		NUM_GEOMETRY
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0, // MVP = MODEL VIEW PROJECTION
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,

		U_TOTAL
	};

public:
	Assignment2();
	~Assignment2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderTrees();
	void RenderHead();
	void RenderBody();
	void RenderUpperArm(int mirror);
	void RenderLowerArm(int mirror);
	void RenderUpperLeg(int mirror);
	void RenderLowerLeg(int mirror);

	void ArrangeTrees(int fromX, int toX, int fromZ, int toZ, int distanceBetweenTrees);

	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Mesh *meshList[NUM_GEOMETRY];

	float rotateAngle, runAnimation;
	float upperLeg, lowerLeg;

	int lowerLegDir;

	bool rightFootFwd;
	bool onLights;

	vector<float> treeArrangementData;

	Camera camera;
	
	Mtx44 MVP;

	MS modelStack, viewStack, projectionStack;

	Light light[1];
};

#endif
#ifndef _CObject_HG_
#define _CObject_HG_

#include "CLight.h"
#include "CVector3f.h"

#include <string>

class CObject
{
public:
	CObject();
	virtual ~CObject();
	
	// Variables
	CVector3f Position;
	CVector3f Rotation;

	float Scale;

	float Mass;
	CVector3f Velocity;
	CVector3f Acceleration;

	//float red, green, blue;
	MaterialInfo material;
	// 
	int numTriangles;
	int numVertices;
	float maxExtent;
	std::wstring plyFileName;

	// Functions
	void moveObject(float timeStep);
	void rotateObject();
	void STOP();
};

#endif
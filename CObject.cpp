#include "CObject.h"

CObject::CObject()
{
	this->Position = CVector3f(0.0f, 0.0f, 0.0f);
	this->Rotation = CVector3f(0.0f, 0.0f, 0.0f);

	this->Scale = 1.0f;
	//this->red = this->green = this->blue = 1.0f;		// White
	//
	this->numTriangles = 0;
	this->numVertices = 0;
	this->maxExtent = 1.0f;

	this->Mass = 1.0f;
	this->Velocity = CVector3f(0.0f, 0.0f, 0.0f);
	this->Acceleration = CVector3f(0.0f, 0.0f, 0.0f);

}

CObject::~CObject()
{

}

// Functions

void CObject::moveObject(float timeStep)
{
	Position.x += Velocity.x * timeStep;
	Position.y += Velocity.y * timeStep;
	Position.z += Velocity.z * timeStep;
}

void CObject::rotateObject()
{

}

void CObject::STOP()
{
	Velocity.x = 0;
	Velocity.y = 0;
	Velocity.z = 0;
}
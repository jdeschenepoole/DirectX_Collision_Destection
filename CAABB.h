#ifndef CAABB_H
#define CAABB_H

#include "CVector3f.h"
#include <vector>
#include <math.h>

#define MAX_LEVEL 6

class CAABB
{
public:
	CAABB( void );
	CAABB(CVector3f newCenter, CVector3f newOffset);
	CAABB(CVector3f newCenter, CVector3f newOffset, int newLevel, int parentID, int thisID);
	~CAABB();
	void GenerateChildren();
	bool IsColliding(CAABB other);
	bool BoxesContainModelGeometry();
	bool TriangleIsInBox(CVector3f &pointA, CVector3f &pointB, CVector3f &pointC);
	void SetTranslation(CVector3f newTranslation);

	CVector3f center;
	CVector3f offset;
	CVector3f translation;
	std::vector<CAABB> childBoxes;
	int hierarchyLevel;
	bool containsModelGeometry;
	void TrimBoxes();  // gets rid of boxes with no geometry in them
	int boxID;  // to determine this box's ID pass in parent's ID number, multiply that by 10, then add
		// number that parent passes into this box upon creation
	int parentBoxID;
};

#endif
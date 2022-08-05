#include "CAABB.h"

CAABB::CAABB( void )
{
	center.x = 0.0f;
	center.y = 0.0f;
	center.z = 0.0f;

	offset.x = 0.0f;
	offset.y = 0.0f;
	offset.z = 0.0f;

	translation.x = 0.0f;
	translation.y = 0.0f;
	translation.z = 0.0f;

	hierarchyLevel = 0;
	containsModelGeometry = false;
	boxID = 0;
	parentBoxID = -1;
}

CAABB::CAABB(CVector3f newCenter, CVector3f newOffset)
{
	center = newCenter;
	offset = newOffset;
	hierarchyLevel = 0;
	containsModelGeometry = false;
	
	boxID = 0;
	parentBoxID = -1;
	GenerateChildren();
}

CAABB::CAABB(CVector3f newCenter, CVector3f newOffset, int newLevel, int parentID, int thisID)
{
	center = newCenter;
	offset = newOffset;
	hierarchyLevel = newLevel;
	containsModelGeometry = false;

	boxID = parentID * 10 + thisID;
	parentBoxID = parentID;

	if (hierarchyLevel != MAX_LEVEL)
		GenerateChildren();
}

CAABB::~CAABB()
{

}

void CAABB::GenerateChildren()
{
	int count = 1; 
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				CVector3f newCenter = center;
				CVector3f newOffset = offset;

				newOffset.x /= 2.0f;
				newOffset.y /= 2.0f;
				newOffset.z /= 2.0f;

				if (i == 0)
					newCenter.x += newOffset.x;
				else
					newCenter.x -= newOffset.x;

				if (j == 0)
					newCenter.y += newOffset.y;
				else
					newCenter.y -= newOffset.y;

				if (k == 0)
					newCenter.z += newOffset.z;
				else
					newCenter.z -= newOffset.z;

				CAABB tempCAABB(newCenter, newOffset, hierarchyLevel + 1, boxID, count);
				childBoxes.push_back(tempCAABB);
				count++;
			}
		}
	}
}

// other is a smaller box than this
bool CAABB::IsColliding(CAABB other)
{
	float leftX = other.center.x - other.offset.x + other.translation.x, rightX = other.center.x + other.offset.x + other.translation.x;
	float downY = other.center.y - other.offset.y + other.translation.y, upY = other.center.y + other.offset.y + other.translation.y;
	float closeZ = other.center.z - other.offset.z + other.translation.z, farZ = other.center.z + other.offset.z + other.translation.z;

	if (((leftX >= center.x - offset.x + translation.x) && (leftX <= center.x + offset.x + translation.x)) ||
		((rightX >= center.x - offset.x + translation.x) && (rightX <= center.x + offset.x + translation.x)))
	{
		if (((downY >= center.y - offset.y + translation.y) && (downY <= center.y + offset.y + translation.y)) ||
			((upY >= center.y - offset.y + translation.y) && (upY <= center.y + offset.y + translation.y)))
		{
			if (((closeZ >= center.z - offset.z + translation.z) && (closeZ <= center.z + offset.z + translation.z)) ||
				((farZ >= center.z - offset.z + translation.z) && (farZ <= center.z + offset.z + translation.z)))
			{
				if (hierarchyLevel == MAX_LEVEL)
					return true;
				else
				{
					for (int i = 0; i < childBoxes.size(); i++)
					{
						if (childBoxes[i].IsColliding(other))
							return true;
					}
				}
			}
		}
	}

	// need to check childboxes in other too

	return false;
}

// Returns whether or not a bounding box or any of its child boxes (and subsequent children) contain
// any model geometry
bool CAABB::BoxesContainModelGeometry()
{
	if (hierarchyLevel == MAX_LEVEL)
		return containsModelGeometry;
	else
	{
		for (int i = 0; i < childBoxes.size(); i++)
		{
			// Recursively check if the child boxes have geometry in then
			if (childBoxes[i].BoxesContainModelGeometry())
				return true;
		}
	}

	return false;
}

void CAABB::TrimBoxes()
{
	if (hierarchyLevel = MAX_LEVEL)
		return;
	
	// start by trimming immediate child boxes that don't have geometry in them
	std::vector<CAABB>::iterator it;
	for (it = childBoxes.begin(); it != childBoxes.end(); it++)
	{
		if (!it->BoxesContainModelGeometry())
		{
			childBoxes.erase(it);
			it = childBoxes.begin();
		}
	}

	// Now recursively trim boxes from the child boxes
	for (it = childBoxes.begin(); it != childBoxes.end(); it++)
		it->TrimBoxes();
}

// Modifying code from Christer Ericson's textbook, page 171
// Returns false whenever the triangle represented by pointA, pointB, and pointC is NOT
// within the current AABB. If it is then the function will recursively call itself to
// check the child boxes of the current box
bool CAABB::TriangleIsInBox(CVector3f &pointA, CVector3f &pointB, CVector3f &pointC)
{
	if ((hierarchyLevel == MAX_LEVEL) && (containsModelGeometry))
		return true;

	// skipping steps about calculating extent and origins due to them already being computed
	float p0, p1, r;
	CVector3f a = pointA - center, b = pointB - center, c = pointC - center;

	// a00
	p0 = a.z * b.y - a.y * b.z;
	p1 = c.z * (b.y - a.y) - c.y * (b.z - a.z);
	r = offset.y * fabs(a.z) + offset.z * fabs(a.y);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a01
	p0 = b.z * c.y - b.y * c.z;
	p1 = a.z * (c.y - b.y) - a.y * (c.z - b.z);
	r = offset.y * fabs(b.z) + offset.z * fabs(b.y);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a02
	p0 = c.z * a.y - c.y * a.z;
	p1 = b.z * (a.y - c.y) - c.y * (a.z - c.z);
	r = offset.y * fabs(c.z) + offset.z * fabs(c.y);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a10
	p0 = a.x * b.z - a.z * b.x;
	p1 = c.x * (b.z - a.z) - c.z * (b.x - a.x);
	r = offset.z * fabs(a.x) + offset.x * fabs(a.z);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a11
	p0 = b.x * c.z - b.z * c.x;
	p1 = a.x * (c.z - b.z) - a.z * (c.x - b.x);
	r = offset.z * fabs(b.x) + offset.x * fabs(b.z);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a12
	p0 = c.x * a.z - c.z * a.x;
	p1 = b.x * (a.z - c.z) - c.z * (a.x - c.x);
	r = offset.z * fabs(c.x) + offset.x * fabs(c.z);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a20
	p0 = a.y * b.x - a.x * b.y;
	p1 = c.y * (b.x - a.x) - c.x * (b.y - a.y);
	r = offset.x * fabs(a.y) + offset.y * fabs(a.x);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a21
	p0 = b.y * c.x - b.x * c.y;
	p1 = a.y * (c.x - b.x) - a.x * (c.y - b.y);
	r = offset.x * fabs(b.y) + offset.y * fabs(b.x);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// a22
	p0 = c.y * a.x - c.x * a.y;
	p1 = b.y * (a.x - c.x) - c.x * (a.y - c.y);
	r = offset.x * fabs(c.y) + offset.y * fabs(c.x);

	if (std::max(-1.0f * std::max(p0, p1), std::min(p0, p1)) > r)
		return false;

	// check if vertices of triangle are within bounds of box
	if ((std::max(a.x, std::max(b.x, c.x)) < -1.0f * offset.x) ||
		(std::min(a.x, std::min(b.x, c.x)) > offset.x))
		return false;
	if ((std::max(a.y, std::max(b.y, c.y)) < -1.0f * offset.y) ||
		(std::min(a.y, std::min(b.y, c.y)) > offset.y))
		return false;
	if ((std::max(a.z, std::max(b.z, c.z)) < -1.0f * offset.z) ||
		(std::min(a.z, std::min(b.z, c.z)) > offset.z))
		return false;

	// Testing based on plane created by triangle
	CVector3f normal, ab = b - a, bc = c - b;
	CVector3f::CrossProduct(ab, bc, normal);
	float d = CVector3f::DotProduct(normal, a);
		
	// Computing projection interval radius of bounding box onto L(t) = t * normal
	r = offset.x * fabs(normal.x) + offset.y * fabs(normal.y) + offset.z * fabs(normal.z);
	// Compute distance of center of bounding box from plane
	float s = CVector3f::DotProduct(normal, center) - d;

	if (fabs(s) <= r)
	{  // triangle is within box since distance of center of bounding box to plane is less than
		// the projection interval radius
		containsModelGeometry = true;

		if (hierarchyLevel < MAX_LEVEL)
		{
			// Recursively check child boxes
			for (int i = 0; i < childBoxes.size(); i++)
				childBoxes[i].TriangleIsInBox(pointA, pointB, pointC);
		}

		return true;
	}

	return false;  // triangle isn't in box so skip checking children
}

void CAABB::SetTranslation(CVector3f newTranslation)
{
	translation = newTranslation;

	if (hierarchyLevel < MAX_LEVEL)
	{
		for (int i = 0; i < childBoxes.size(); i++)
			childBoxes[i].SetTranslation(translation);
	}
}


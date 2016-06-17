#include "orientedBoundingBox.h"

OBB::OBB()
{

}

OBB::OBB(float halfExtentX, float halfExtentY, float rotation, Vector<float> position)
{
	
	OBB::centrePos = position;
	halfExtents[0] = halfExtentX;
	halfExtents[1] = halfExtentY;
	OBB::rotation = rotation;
}



void OBB::MoveBoundingBox(Vector<float> & position)
{

	OBB::centrePos = position;
}

void OBB::RotateBoundingBox(float rotation)
{
	OBB::rotation = rotation;
}

Vector<float> OBB::GetHalfExtents()
{
	return Vector<float>(halfExtents[0], halfExtents[1]);
}


float OBB::GetRotation()
{
	return rotation;
}
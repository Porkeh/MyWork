#include "circleBoundingBox.h"

CircleBB::CircleBB()
{

}

CircleBB::CircleBB(float radius, Vector<float> position)
{
	CircleBB::radius = radius; //!< Set the radius to the radius
	CircleBB::centrePos = position; //!< Set the position to the position
}

float CircleBB::GetRadius()
{
	return radius; //!< Return the radius
}

void CircleBB::MoveBoundingBox(Vector<float> & position)
{

	CircleBB::centrePos = position; //!< Set the position to the position
}

void CircleBB::SetRadius(float rad)
{
	radius = rad; //!< Set the radius to the radius
}


#include "Collidable.h"
#include <cmath>
#include <algorithm>

Collidable::Collidable()
{

}

bool Collidable::CircleToCircle (CircleBB &other) 
{
	
	float radSum = bounds.GetRadius()+other.GetRadius();
	Vector<float> dist =    other.GetPosition() - bounds.GetPosition();
	float mag = dist.GetMagnitude();
	if (mag < radSum)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Collidable::CircleToOBB(CircleBB &other)
{
	CircleBB movedCircle;
	movedCircle.MoveBoundingBox( other.GetPosition() - oBounds.GetPosition() );
	float rads = oBounds.GetRotation()*(3.14 / 180);
	//movedCircle
	float x = movedCircle.GetPosition().GetX()*std::cos(-rads) + -movedCircle.GetPosition().GetY() * std::sin(-rads);
	float y = movedCircle.GetPosition().GetX()*std::sin(-rads) + movedCircle.GetPosition().GetY() * std::cos(-rads);
	//x += oBounds.GetPosition().GetX();
	//y += oBounds.GetPosition().GetY();
	movedCircle.SetRadius(other.GetRadius());
	movedCircle.MoveBoundingBox(Vector<float>(x, y));
	//return movedCircle;
	
	Vector<float> dist = movedCircle.GetPosition();
	Vector <float> clamp = dist;

	if (dist.GetX() >= 0)
	{ 
		clamp.SetX(std::min(dist.GetX(), oBounds.GetHalfExtents().GetX())); 
	}

	if (dist.GetX() < 0) 
	{
		clamp.SetX(std::max(dist.GetX(), -oBounds.GetHalfExtents().GetX()));
	}

	if (dist.GetY() >= 0) 
	{ 
		clamp.SetY(std::min(dist.GetY(), oBounds.GetHalfExtents().GetY())); 
	}

	if (dist.GetY() < 0) 
	{
		clamp.SetY(std::max(dist.GetY(), -oBounds.GetHalfExtents().GetY()));
	}

	Vector<float> diff = dist-clamp;
	float distance = diff.GetMagnitude() - other.GetRadius();
	if (distance < 0)
	{
		diff.Normalise();
		cp = diff * distance;
		return true;
	}
	else
	{
		return false;
	}
}
Vector<float> Collidable::GetContactPoint()
{
	return cp;
}
CircleBB  Collidable::GetBounds() const
{
	
	return  bounds;
}

OBB Collidable::GetoBounds() const
{
	return oBounds;
}
void Collidable::MoveBox(Vector<float> newPos)
{
	oBounds.MoveBoundingBox(newPos);
}

void Collidable::RotateOBB(float rotation)
{
	oBounds.RotateBoundingBox(rotation);
}
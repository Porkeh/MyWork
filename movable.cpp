#include "movable.h"
#include <iostream>

Movable::Movable() 
{
	m_acceleration = Vector<float>(0, 0);
	m_position = Vector<float>(0, 0);
	m_velocity.Zero();
	m_rotVel = Vector<float>(0, 0);
	resolvedVel.Zero();
	m_fRotationAngle = 0.f;
	m_fAngleIncrement = 0.f;
	m_fFriction = 0.6f;
	m_fGravity = 0.98f;
	m_prevPosition.Zero();

}



Vector<float> Movable::GetPosition() const
{
	return m_position;
}
void Movable::SetPosition(Vector<float> pos)
{
	m_position = pos;
}
void Movable::SetVelocity(Vector<float> vel)
{
	m_velocity = vel;
}
void Movable::SetAcceleration(float acc)
{
	m_acceleration.SetBoth(acc,acc);
}
void Movable::SetRotation(float rot)
{
	m_fRotationAngle = rot;
	
}
float Movable::GetRotation()
{
	return m_fRotationAngle;
}
Vector<float> Movable::GetVelocity()
{
	return m_rotVel;
}

Vector<float> Movable::GetAcceleration()
{
	return m_acceleration;
}
void Movable::SetRotationIncrement(float rot)
{
	m_fAngleIncrement = rot;
}
float Movable::IncrementAngle()
{
	m_fRotationAngle += m_fAngleIncrement;
	return m_fRotationAngle;
}

float Movable::GetInverseMass()
{
	return m_invMass;
}

void Movable::RotationCollisionResolution( Movable &other, Vector<float> contactPoint)
{
	

	float e = 0.7;

	Vector<float> colNormal = m_position- other.GetPosition();
	colNormal.Normalise();
	//float relvel = (m_velocity - other.GetVelocity()).DotProduct(colNormal);
	//float denom = relvel * -(1 + e);
	//float numer = GetInverseMass() + other.GetInverseMass();
	//float j = denom / numer;
	//float k = j*colNormal.GetX();
	//float l = k / m_mass;
	//////Vector<float> positiondiff = m_position - m_prevposition;
	//m_position = m_prevPosition;
	////m_prevposition += positiondiff;
	//resolvedVel.SetX(m_velocity.GetX() + ((j*colNormal.GetX()) / m_mass));
	//resolvedVel.SetY(m_velocity.GetY() + ((j*colNormal.GetY()) / m_mass));
	
	float yRest = (-(1 + e) * colNormal.GetY() * colNormal.DotProduct(m_velocity));
	resolvedVel.SetY(m_velocity.GetY() + yRest);
	m_position = m_prevPosition;
	
	
	if (resolvedVel.GetY() == 0)
	{
		resolvedVel.SetY(resolvedVel.GetX());
	}
	std::cout << m_velocity.GetX() << " " << m_velocity.GetY() << std::endl;
	
	
	
	
	
}

Vector<float> Movable::GetResolvedVel()
{
	return resolvedVel;
}

void Movable::CollisionResolved()
{
	resolvedVel.Zero();
	
}

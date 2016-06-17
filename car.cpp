#include "car.h"
#include <iostream>
Car::Car(sf::Texture &texture, Vector<float> position)
{
	m_texture = texture;
	m_sprite = sf::Sprite(texture);
	m_sprite.setPosition(position.GetX(),position.GetY());
	m_position.SetBoth(position.GetX(), position.GetY());
	m_sprite.setOrigin((float)m_texture.getSize().x/2, (float)m_texture.getSize().y/2);
	MAX_ACCELERATION = 5;
	bCanAccelerate = false;
	bCanDeccelerate = false;
	bCollided = false;
	m_acceleration.SetBoth(0, 0);
	m_velocity.SetBoth(0, 0);
	m_mass = 100;
	m_invMass = 1 / m_mass;
	bounds = CircleBB(m_texture.getSize().y/2.0f, m_position);
	oBounds = OBB(m_texture.getSize().x / 2.0f, m_texture.getSize().y / 2.0f, m_sprite.getRotation(), m_position);
	fSteeringAngle = 90 * 0.0174;
	fSteeringIncrement = 0;
	fHeadingAngle = 0;
	m_fSteeringVector.Zero();
	m_fHeadingVector.Zero();
	m_fFrontWheel.Zero();
	m_fBackWheel.Zero();
	iSteerDir = 0;
	
}
Car::Car()
{

}

void Car::update(float  &timeStep)
{
	
	
	IncrementSteeringAngle();
	bounds.MoveBoundingBox(m_position);

	if (bCollided == false)
	{
		m_prevPosition = m_position;
	}
	
	if (bCanAccelerate )
	{
		Accelerate(0, 5);
		
	}
	else
	if (bCanDeccelerate )
	{
		Accelerate(0, -5);
	}
	else
	{
		Accelerate(0, 0);
	}

	if (iSteerDir == 0)
	{
		
		fHeadingAngle = fSteeringAngle;
		fSteeringAngle = fHeadingAngle;
			
		

	
	}
	if (iSteerDir == 1)
	{
		if (fSteeringAngle - fHeadingAngle < 45 * 0.0174)
		{
			fSteeringAngle += 2 * 0.0174;
		}
	}
	if (iSteerDir == 2)
	{
		if (fSteeringAngle - fHeadingAngle > -45 * 0.0174)
		{
			fSteeringAngle -= 2 * 0.0174;
		}
	}
	if (m_velocity.GetY() > -0.1 && m_velocity.GetY() < 0.1)
	{
		if (!bCanAccelerate && !bCanDeccelerate)
		{
			m_velocity.Zero();
		}

	}
	move(timeStep);
	m_fRotationAngle = fSteeringAngle * 180 / 3.14f;
	m_sprite.setPosition(m_position.GetX(),m_position.GetY());
	m_sprite.setRotation(m_fRotationAngle);
}

void Car::Accelerate(float x, float y)
{
	m_acceleration.SetBoth(x, y);
}
void Car::SetCanAccelerate(bool b)
{
	bCanAccelerate = b;
}

void Car::SetCanDeccelerate(bool b)
{
	bCanDeccelerate = b;
}

void Car::move(float  &timeStep)
{
	float t = timeStep; 

	if (bCollided)
	{
		m_velocity = resolvedVel;
		
	}
	
	m_acceleration += -m_velocity*(m_fFriction*m_fGravity);

	if (m_velocity.GetX() > MAX_ACCELERATION)
	{
		m_velocity.SetX(MAX_ACCELERATION);
	}
	if (m_velocity.GetY() > MAX_ACCELERATION)
	{
		m_velocity.SetY(MAX_ACCELERATION);
	}
	
	if (m_velocity.GetX() < -MAX_ACCELERATION)
	{
		m_velocity.SetX(-MAX_ACCELERATION);
	}
	if (m_velocity.GetY() < -MAX_ACCELERATION)
	{
		m_velocity.SetY(-MAX_ACCELERATION);
	}
	m_velocity += m_acceleration * timeStep;

	
	
	m_rotVel.SetX(m_velocity.GetX()*std::cos(fSteeringAngle) + m_velocity.GetY() * -std::sin(fSteeringAngle));
	m_rotVel.SetY(m_velocity.GetX()*std::sin(fSteeringAngle) + m_velocity.GetY() * std::cos(fSteeringAngle));
	Vector<float> d = m_velocity;


	m_fSteeringVector.SetX(std::cos(fSteeringAngle) * 0 + -std::sin(fSteeringAngle) * -1);
	m_fSteeringVector.SetY(std::sin(fSteeringAngle) * 0 + std::cos(fSteeringAngle) * -1);

	m_fHeadingVector.SetX(std::cos(fHeadingAngle) * 0 + -std::sin(fHeadingAngle) * -1);
	m_fHeadingVector.SetY(std::sin(fHeadingAngle) * 0 + std::cos(fHeadingAngle) * -1);

	m_fFrontWheel.SetX(m_position.GetX() + m_fHeadingVector.GetX() * (m_texture.getSize().y / 2));
	m_fFrontWheel.SetY(m_position.GetY() + m_fHeadingVector.GetY() * (m_texture.getSize().y / 2));

	m_fBackWheel.SetX(m_position.GetX() - m_fHeadingVector.GetX() * (m_texture.getSize().y / 2));
	m_fBackWheel.SetY(m_position.GetY() - m_fHeadingVector.GetY() * (m_texture.getSize().y / 2));

	m_fFrontWheel.SetX(m_fFrontWheel.GetX() + (m_fSteeringVector.GetX() * d.GetY()));
	m_fFrontWheel.SetY(m_fFrontWheel.GetY() + (m_fSteeringVector.GetY() * d.GetY()));

	m_fBackWheel.SetX(m_fBackWheel.GetX() + (m_fHeadingVector.GetX() * d.GetY()));
	m_fBackWheel.SetY(m_fBackWheel.GetY() + (m_fHeadingVector.GetY() * d.GetY()));

	m_position.SetX((m_fFrontWheel.GetX() + m_fBackWheel.GetX()) / 2);
	m_position.SetY((m_fFrontWheel.GetY() + m_fBackWheel.GetY()) / 2);

	float prevHeading = fHeadingAngle;
	fHeadingAngle = std::atan2f((m_fFrontWheel.GetY() - m_fBackWheel.GetY()), (m_fFrontWheel.GetX() - m_fBackWheel.GetX()));

	fHeadingAngle = fHeadingAngle + 3.14159265359f / 2;

	fSteeringAngle = fSteeringAngle + (fHeadingAngle - prevHeading);
	
	m_acceleration.Zero();
	
}

void Car::SetCollided(bool b)
{
	bCollided = b;
}
bool Car::GetCollided()
{
	return bCollided;
}
void Car::SetSteeringAngle(int angle)
{
	
	
	iSteerDir = angle;
	
}

void Car::IncrementSteeringAngle()
{
	
	fSteeringAngle += fSteeringIncrement;
	

}

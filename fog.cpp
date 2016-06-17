#include "fog.h"


Fog::Fog()
{

}

Fog::Fog(sf::Texture &texture, float x, float y, float z, float speed, int dir)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(x, y);

	m_velocity = Vector<float>(1, 0);
	if (dir % 2 == 0)
	{
		Fog::speed = speed;
	}
	else
	{
		Fog::speed = -speed;
	}
	Fog::z = z;
	m_position = Vector<float>(x, y);
}


void Fog::move(float &timeStep)
{
	if (m_position.GetX() > 2100)
	{
		m_position.SetX(-200);
	}
	if (m_position.GetX() < -200)
	{
		m_position.SetX(2100);
	}
	if (m_velocity.GetX() < 100)
	{
		m_acceleration = Vector<float>(speed * z * 1, 0);
		m_velocity += m_acceleration * timeStep;
	}
	m_position += m_velocity * timeStep;
	m_sprite.setPosition(m_position.GetX(),m_position.GetY());
	
}


float Fog::GetZ() const
{
	return z;
}
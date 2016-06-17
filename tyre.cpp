#include "tyre.h"



Tyre::Tyre()
{

}

Tyre::Tyre(sf::Texture &texture, Vector<float> position)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(position.GetX(),position.GetY());
	m_sprite.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
	m_position = position;
	bounds = CircleBB(texture.getSize().x / 2, Vector<float>(position.GetX(), position.GetY()));
	m_invMass = 0;
	m_mass = 50;
}

void Tyre::move(float &timeStep)
{

}

void Tyre::update(float &timeStep)
{

}


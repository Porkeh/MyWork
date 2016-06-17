#include "background.h"


Background::Background()
{
}


Background::Background(sf::Texture &texture)
{
	m_sprite.setTexture(texture); //!< Set the texture
	m_sprite.setPosition(-600, -250); //!< Set the position
}

void Background::Update(Vector<float> movement)
{
	// Check if the movement is moving
	if (movement.GetX() != 0 || movement.GetY() != 0)
	{
		//Check if one of the movements values is greater than 1 or -1
		if ((movement.GetX() > 1 || movement.GetX() < -1 || movement.GetY() > 1 || movement.GetY() < -1))
		{

			movement.Normalise(); //!< Normalise the movement value
		}

		m_sprite.move(movement.GetX(), movement.GetY()); //!< Move the sprite by the movement value
	}
}
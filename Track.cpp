#include "track.h"


Track::Track()
{
}

Track::Track(sf::Texture &texture)
{
	m_sprite.setTexture(texture);
	m_sprite.setPosition(0, 0);
}
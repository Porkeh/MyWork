#include "drawable.h"


Drawable::Drawable()
{

}


void Drawable::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
	target.draw(m_sprite, state);
}

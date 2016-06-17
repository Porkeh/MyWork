#include "menu.h"


Menu::Menu()
{
	
}

Menu::Menu(TextureManager textureManager, sf::RenderWindow &window)
{
	texManager = textureManager;
	backGround.setTexture(texManager.GetTexture(0));
	if (!font.loadFromFile(".\\resources\\lady_radical.ttf"))
	{

	}
	
	Initialize(window);



}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.setView(menuCam);
	target.draw(backGround);
	for (int i = 0; i < text.size(); i++)
	{
		target.draw(text.at(i));
	}
}

void Menu::update()
{
	if (r > 0)
	{
		r -= 1;
	}
	else
	{
		r = 255;
	}
	if (g > 0)
	{
		g-= 2;
	}
	else
	{
		g = 255;
	}
	if (b > 0)
	{
		b-= 3;
	}
	else
	{
		b = 255;
	}
	text.at(selected).setColor(sf::Color(r,g,b));
	
	
}

void Menu::processKeyDown(sf::Keyboard::Key key, int &state)
{
	switch (key)
	{
	case sf::Keyboard::S:
		text.at(selected).setColor(sf::Color(255, 255, 255));
		selected--;
		if (selected < 0)
		{
			selected = 1;
		}
		break;

	case sf::Keyboard::W:
		text.at(selected).setColor(sf::Color(255, 255, 255));
		selected++;
		if (selected > 1)
		{
			selected = 0;
		}
		break;
	case sf::Keyboard::Return:
		
		if (selected == 1)
		{
			state = 2;
		}
		if (selected == 0)
		{
			state = 1;
		}
		break;


	default:
		break;
	}
}


void Menu::Initialize(sf::RenderWindow &window)
{
	sf::Text temp;
	temp.setFont(font);
	temp.setString("Play");
	temp.setScale(2, 2);

	temp.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 4);
	r = 255;
	g = 255;
	b = 255;
	temp.setColor(sf::Color(r, g, b));
	temp.setCharacterSize(72);
	text.push_back(temp);
	temp.setString("Exit");

	temp.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 4 * 2);
	text.push_back(temp);
	menuCam.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	menuCam.setSize(window.getSize().x, window.getSize().y);
	window.setView(menuCam);
	selected = 0;
}
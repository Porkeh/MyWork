
#include "SFML/graphics.hpp"
#include "SFML/Audio.hpp"
#include "game.h"
#include "menu.h"
#include "textureManager.h"
#include <vector>
#include <string>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Racing Game");
	TextureManager texManager;
	texManager.SetBaseDir(".\\resources\\");
	vector<string> texLocations;
	texLocations.push_back("bg1.png");
	texLocations.push_back("car.png");
	texLocations.push_back("cloud.png");
	texLocations.push_back("lap_start.png");
	texLocations.push_back("track.png");
	texLocations.push_back("tyre.png");
	texManager.Load(texLocations);
	Menu menu(texManager, window);
	Game game(texManager);
	
	sf::Clock clock;
	sf::Music music;
	if (!music.openFromFile(".\\resources\\music.ogg"));
	{

	}
	music.setLoop(true);
	music.setVolume(25);
	music.play();

	enum GameState { inMenu, playing, exit, finished };

	GameState gameState;
	gameState = GameState::inMenu;
	int stateIter = 0;

	while (window.isOpen())
	{
		sf::Event event;
		switch (stateIter)
		{
		case 0:
			gameState = GameState::inMenu;
			break;
		case 1:
			gameState = GameState::playing;
			break;
		case 2:
			gameState = GameState::exit;
			break;
		case 3:
			gameState = GameState::finished;
			break;
		default:
			break;
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if (event.type == sf::Event::KeyPressed)
			{
				switch (gameState)
				{
				case inMenu:
					menu.processKeyDown(event.key.code, stateIter);
					break;
				case playing:
					game.processKeyDown(event.key.code);
					break;
				default:
					break;
				}
				
			}

			if (event.type == sf::Event::KeyReleased)
			{
				switch (gameState)
				{
				case inMenu:
					break;
				case playing:
					game.processKeyUp(event.key.code);
					break;
				default:
					break;
				}
				
				
			}
		}


		if (clock.getElapsedTime().asSeconds() > 0.0167)
		{
			float timeStep = clock.getElapsedTime().asSeconds();
			switch (gameState)
			{
			case inMenu:
				menu.update();
				break;
			case playing:
				game.Update(timeStep, window, stateIter);
				break;
			case exit:
				window.close();
				break;
			case finished:
				//menu.Initialize(window);
				stateIter = 0;
			default:
				break;
			}
			//game.Update(timeStep, window);
			clock.restart();

		}


		window.clear(sf::Color::Black);

		switch (gameState)
		{
		case inMenu:
			window.draw(menu);
			break;
		case playing:
			window.draw(game);
			break;
		default:
			break;
		}
		//window.draw(game);
		window.display();

	}

}
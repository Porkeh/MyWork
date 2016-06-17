#include "game.h"


Game::Game()
{

}

Game::Game(TextureManager &texture)
{
	texManager = texture;
	
	setup = false;
	
}


void Game::processKeyDown(sf::Keyboard::Key key)
{
	if (!raceOver)
	{
		switch (key)
		{
		case sf::Keyboard::Key::D:
			//acceleration.SetX(10);
			//playerCar.SetRotationIncrement(20.f*0.167);
			playerCar.SetSteeringAngle(1);
			break;
		case sf::Keyboard::Key::A:
			//acceleration.SetX(-10);
			//playerCar.SetRotationIncrement(-20.f*0.167);
			playerCar.SetSteeringAngle(2);
			break;
		case sf::Keyboard::Key::W:
			//playerCar.Accelerate(0, -10);
			playerCar.SetCanAccelerate(true);
			break;
		case sf::Keyboard::Key::S:
			playerCar.SetCanDeccelerate(true);
			break;
		default:
			break;
		}
	}
	
}

void Game::processKeyUp(sf::Keyboard::Key key)
{
	
	switch (key)
	{
	case sf::Keyboard::Key::D:
		//v.SetX(0.f);
		//playerCar.SetVelocity(v);
		//playerCar.SetRotationIncrement(0.f);
		playerCar.SetSteeringAngle(0);
		break;
	case sf::Keyboard::Key::A:
		//v.SetX(0.f);
		//playerCar.SetVelocity(v);
		//playerCar.SetRotationIncrement(0.f);
		playerCar.SetSteeringAngle(0);
		break;
	case sf::Keyboard::Key::W:
		playerCar.SetCanAccelerate(false);
		
		//playerCar.Accelerate(0,0);
		break;
	case sf::Keyboard::Key::S:
		//v.SetY(0.f);
		//playerCar.SetVelocity(v);
		playerCar.SetCanDeccelerate(false);
		break;
	default:
		break;
	}
	
}

void Game::Update(float &fTimeStep, sf::RenderWindow &window, int &stateIndex)
{
	if (!setup)
	{
		Initialize();
		lapTimer.restart();
		setup = true;
		
	}
	if (raceOver)
	{
		if (timer.getElapsedTime().asSeconds() > 2.00)
		{
			setup = false;
			stateIndex = 3;
		}

	}
	playerCar.update(fTimeStep);
	bg.Update(playerCar.GetVelocity());
	for (int i = 0; i < fog.size(); i++)
	{
		fog.at(i).move(fTimeStep);
	}
	cam1.setCenter(playerCar.GetPosition().GetX(),playerCar.GetPosition().GetY());
	lapTime.setPosition(cam1.getCenter().x - cam1.getSize().x / 2 + 20, cam1.getCenter().y + cam1.getSize().y /2 - 60);
	string temp = to_string(lapTimer.getElapsedTime().asSeconds());
	lapTime.setString("Time: " + temp);
	for (int i = 0; i < 4; i++)
	{
		completedLapTimes[i].setPosition(cam1.getCenter().x + cam1.getSize().x /2 - 75, cam1.getCenter().y - cam1.getSize().y /2 + 10 * (i + 1));
	}
	completedLapTimes[3].setPosition(cam1.getCenter().x + cam1.getSize().x / 2 - 99, cam1.getCenter().y - cam1.getSize().y / 2 + 10 * (3 + 1));
	window.setView(cam1);
	bool hasCollided = false;
	for (int i = 0; i < tyres.size(); i++)
	{
		if (playerCar.CircleToCircle( tyres.at(i).GetBounds()))
		{
		
			playerCar.MoveBox(playerCar.GetPosition());
			playerCar.RotateOBB(playerCar.GetRotation());
		
				if (playerCar.CircleToOBB(tyres.at(i).GetBounds()))
				{
				
					
				
						
							if ( prevCollided != i && !hasCollided)
							{

								playerCar.RotationCollisionResolution(tyres.at(i), playerCar.GetContactPoint());
								prevCollided = i;
							}
						
					
						
						
						std::cout << "Collide";
						
						
					
						hasCollided = true;
						
					
					
					
				
				

				}
			
			
		}
		
		
	}

	if (!hasCollided)
	{
		playerCar.SetCollided(false);
		


	}
	else
	{
		playerCar.SetCollided(true);
	}
	
	
	if (checkPoint.CircleToOBB(playerCar.GetBounds()))
	{
		checkPoint.move(fTimeStep);
		int prevLapsCompleted = iLapsCompleted;
		iLapsCompleted = checkPoint.GetLapsCompleted();
		if (iLapsCompleted != prevLapsCompleted)
		{
			completedLapTimes[iLapsCompleted - 1].setString(completedLapTimes[iLapsCompleted - 1].getString() + to_string(lapTimer.getElapsedTime().asSeconds() - previousLapTime));
			previousLapTime = lapTimer.getElapsedTime().asSeconds();
		}
		if (checkPoint.lapsComplete())
		{
			completedLapTimes[3].setString(completedLapTimes[3].getString() + to_string(lapTimer.getElapsedTime().asSeconds()));
			raceOver = true;
			timer.restart();
		}
		
	}
	
	
}


void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

	target.clear(sf::Color::Green);
	target.draw(bg, states);
	for (int i = 0; i < fog.size(); i++)
	{
		if (fog.at(i).GetZ() < 5)
		{
			target.draw(fog.at(i));
		}
	}
	target.draw(track, states);
	target.draw(lapStart, states);
	for (int i = 0; i < tyres.size(); i++)
	{
		target.draw(tyres.at(i), states);
	}
	//target.draw(tyres[0], states);
	
	target.draw(playerCar, states);
	
	for (int i = 0; i < fog.size(); i++)
	{
		if (fog.at(i).GetZ() >= 5)
		{
			target.draw(fog.at(i));
		}
	}
	target.draw(lapTime);
	for (int i = 0; i < 4; i++)
	{
		target.draw(completedLapTimes[i]);
	}
	//sf::CircleShape box = sf::CircleShape(playerCar.GetBounds().GetRadius(), 300);
	//box.setOrigin(box.getRadius(), box.getRadius());
	//box.setPosition(playerCar.GetPosition().GetX(), playerCar.GetPosition().GetY());
	//target.draw(box);
	
}


void Game::Initialize()
{
	startPos = Vector<float>(346.f, 130.f);
	playerCar = Car(texManager.GetTexture(1), startPos);
	//playerCar.SetRotation(90);
	//	tyres[0] = Tyre(textures[1], Vector<float>(700, 700));
	track = Track(texManager.GetTexture(4));
	tyreLoader.ReadFile(tyrePos);
	for (int i = 0; i < tyrePos.size(); i++)
	{
		tyres.push_back(Tyre(texManager.GetTexture(5), tyrePos.at(i)));
	}

	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		fog.push_back(Fog(texManager.GetTexture(2), float(rand() % 1900 + 1), float(rand() % 1000 + 1), rand() % 10 + 1, rand() % 5 + 1, rand() % 100));
	}
	lapStart.setTexture(texManager.GetTexture(3));
	lapStart.setPosition(318, 86);
	bg = Background(texManager.GetTexture(0));
	Vector<float> positions[5] = { Vector<float>(680, 605), Vector<float>(1313, 377), Vector<float>(1391, 834), Vector<float>(201, 681), Vector<float>(318, 130) };
	checkPoint = CheckPoint(positions);
	iLapsCompleted = 0;
	cam1 = sf::View(sf::Vector2f(200, 200), sf::Vector2f(1920, 1080));
	cam1.zoom(0.3f);
	lapTimer.restart();
	if (!font.loadFromFile(".\\resources\\ui.ttf"))
	{
		std::cout << "Error" << std::endl;
	}
	lapTime.setPosition(cam1.getCenter().x - cam1.getSize().x / 2, cam1.getCenter().y - cam1.getSize().y - 20);
	lapTime.setFont(font);
	lapTime.setString("Time: ");
	lapTime.setColor(sf::Color::White);
	for (int i = 0; i < 4; i++)
	{
		completedLapTimes[i].setFont(font);
		completedLapTimes[i].setPosition(cam1.getCenter().x + cam1.getSize().x / 2, cam1.getCenter().y + cam1.getSize().y - 20 * (i + 1));
		completedLapTimes[i].setString("Lap " + to_string(i + 1) + ":  ");
		completedLapTimes[i].setColor(sf::Color::White);
		completedLapTimes[i].setCharacterSize(10);
	}
	completedLapTimes[3].setString("Total Time:  ");
	previousLapTime = 0;
	
	raceOver = false;
}
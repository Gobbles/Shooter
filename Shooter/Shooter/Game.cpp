#include "Game.h"

Game::Game() : window(sf::VideoMode(1024,768),"Josh & Higgins vs The World", sf::Style::Close)
{
	if(!mapTexture.loadFromFile("Art/background.png"))
	{ }
	mapSprite.setTexture(mapTexture);

	Player1 = std::make_shared<Higgins>(Higgins());
	
	mDrawables.push_back(Player1);
}

Game::~Game()
{

}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	static const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (window.isOpen())
    {
		//ProcessEvents();
		timeSinceLastUpdate += clock.restart();
		
		while(timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			ProcessEvents();
			Update(timePerFrame.asSeconds());
		}
		Draw();
	}
}
void Game::ProcessEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
    {
		CheckEvents(event);
    }
}
void Game::CheckEvents(sf::Event &event)
{
	//check for our Input Events
	switch(event.type)
	{
		case sf::Event::Closed:
		{
			window.close();
		}
		case sf::Event::KeyPressed:
		{
			switch(event.key.code)
			{
				case sf::Keyboard::A:
				{
					break;
				}
				case sf::Keyboard::D:
				{
					break;
				}
				case sf::Keyboard::W:
				{
					break;
				}
				case sf::Keyboard::S:
				{
					break;
				}
				case sf::Keyboard::Space:
				{
					break;
				}
				case sf::Keyboard::Q:
				{
					break;
				}
				case sf::Keyboard::E:
				{
					break;
				}
			}
			break;
		}
		case sf::Event::KeyReleased:
		{
			switch(event.key.code)
			{
				case sf::Keyboard::A:
				{
					break;
				}
				case sf::Keyboard::D:
				{
					break;
				}
				case sf::Keyboard::W:
				{
					break;
				}
				case sf::Keyboard::S:
				{
					break;
				}
			}
			break;
		}
	}
}

void Game::Update(float timePassed)
{
	//std::cout << "Updating\n";
	for(int i = 0; i < mDrawables.size(); ++i)
	{
		mDrawables[i]->Update(timePassed);
	}
}

void Game::Draw()
{
	//std::cout << "Drawing\n";
	window.clear();
	window.draw(mapSprite);
	for(int i = 0; i < mDrawables.size(); ++i)
	{
		mDrawables[i]->Draw(window);
	}
	window.display();
}
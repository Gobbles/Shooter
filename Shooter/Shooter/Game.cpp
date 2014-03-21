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
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

	while (window.isOpen())
    {
		//ProcessEvents();
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
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
	Player1->CheckInput(event);
	//check for our Input Events
	switch(event.type)
	{
		case sf::Event::Closed:
		{
			window.close();
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
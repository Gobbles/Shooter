#include "Game.h"

Game::Game() : window(sf::VideoMode(1024,768),"Josh & Higgins vs The World", sf::Style::Close)
{
	window.setKeyRepeatEnabled(false);
	if(!mapTexture.loadFromFile("Art/background.png"))
	{ }
	mapSprite.setTexture(mapTexture);

	Player1 = std::shared_ptr<Higgins>(new Higgins());

	mGameEntities.push_back(Player1);

	mShot = std::unique_ptr<ShotLevelOne>(new ShotLevelOne(sf::Vector2f(Player1->mPosition.x + 40, Player1->mPosition.y - 100),false));
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
	Player1->ProcessInput(event);
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
	for(int i = 0; i < mGameEntities.size(); ++i)
	{
		//mDrawables[i]->Update(timePassed);
		IUpdateable* updateable = dynamic_cast<IUpdateable*>(mGameEntities[i].get());
		if(updateable != nullptr)
		{
			updateable->Update(timePassed);
		}
	}
	mShot->Update(timePassed);
	//Player1->Update(timePassed);
}

void Game::Draw()
{
	//std::cout << "Drawing\n";
	window.clear();
	window.draw(mapSprite);
	for(int i = 0; i < mGameEntities.size(); ++i)
	{
		IDrawable* drawable = dynamic_cast<IDrawable*>(mGameEntities[i].get());
		if(drawable != nullptr)
		{
			drawable->Draw(window);
		}
	}
	mShot->Draw(window);
	//Player1->Draw(window);
	window.display();
}
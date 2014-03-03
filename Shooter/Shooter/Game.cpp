#include "Game.h"

Game::Game() : window(sf::VideoMode(1024,768),"random shooter", sf::Style::Close)
{

}

Game::~Game()
{

}

void Game::Run()
{
	while (window.isOpen())
    {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		Update();
		Draw();
	}
}

void Game::Update()
{

}

void Game::Draw()
{
	window.clear();
	window.display();
}
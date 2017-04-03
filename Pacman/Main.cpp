#include <SFML/Graphics.hpp>
#include "Game.h"

void CheckPollEvents(sf::RenderWindow & pWindow);
void Update(Game & pGame, sf::Clock & pGameTime, sf::RenderWindow & pWindow);
void Draw(sf::RenderWindow & pWindow, Game & pGame);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		
	sf::RenderWindow window(sf::VideoMode(1280, 736), "Pacman");
	Game game;
	sf::Clock gameTime;

	// Run until the game has exited
	while (window.isOpen())
	{
		CheckPollEvents(window);
		Update(game, gameTime, window);
		Draw(window, game);
	}

	return 0;
}

/*
 Update the Game
*/
void Update(Game & pGame, sf::Clock & pGameTime, sf::RenderWindow & pWindow)
{
	pGame.Update(pGameTime.restart().asSeconds(), pWindow);
}

/*
 Draw the game
*/
void Draw(sf::RenderWindow & pWindow, Game & pGame)
{
	pWindow.clear();
	pWindow.draw(pGame);
	pWindow.display();
}

/*
 Get Windows poll events
*/
void CheckPollEvents(sf::RenderWindow & pWindow)
{
	sf::Event event;
	while (pWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			pWindow.close();
		}
	}
}
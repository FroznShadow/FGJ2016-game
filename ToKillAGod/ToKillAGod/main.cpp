#include <SFML/Graphics.hpp>
#include <SFML\System.hpp>

#include "StateManager.hpp"
#include "ResourceManager.h"
#include "GameObject.h"
#include "StateManager.hpp"
#include "menuState.h"
#include "Button.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "TOKILLAGOD!");

	sf::Clock deltaClock;

	ResourceManager* RM = ResourceManager::getInstance();
	StateManager SM;
	SM.setState(new MenuState);

	while (window.isOpen())
	{
		sf::Time deltaTime = deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		SM.update(deltaTime.asSeconds());
		window.clear();

		//draw
		SM.draw(window);

		//end draw
		window.display();
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "GameObject.h"
#include "StateManager.hpp"
#include "menuState.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(255, 127, 0, 255));

	ResourceManager* RM = ResourceManager::getInstance();
	StateManager SM;
	SM.setState(new MenuState);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		SM.update(0.1);
		window.clear();

		//draw
		window.draw(shape);
		SM.draw(window);

		//end draw
		window.display();
	}

	return 0;
}
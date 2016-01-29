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
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(255, 127, 0, 255));

	sf::Clock deltaClock;

	ResourceManager* RM = ResourceManager::getInstance();
	StateManager SM;
	SM.setState(new MenuState);

	CircleButton circlejerk(400, 400, 100);
	RectangleButton rectButt(200, 200, 200, 50);

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
		rectButt.draw(window);
		circlejerk.draw(window);
		window.draw(shape);
		SM.draw(window);

		//end draw
		window.display();
	}

	return 0;
}
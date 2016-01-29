#include <SFML/Graphics.hpp>

#include "StateManager.hpp"
#include "ResourceManager.h"
#include "GameObject.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(255, 127, 0, 255));

	sf::Clock deltaClock;

	ResourceManager* RM = ResourceManager::getInstance();
	StateManager SM;

	GameObject* go = new GameObject();
	go->M_set_Texture(*(RM->getTexture("default")));

	while (window.isOpen())
	{
		sf::Time deltaTime = deltaClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		SM.update(deltaTime.asSeconds());
		window.draw(shape);
		go->M_draw(window);
		window.display();
	}

	return 0;
}
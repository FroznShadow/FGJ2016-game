#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "GameObject.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color(255, 127, 0, 255));

	ResourceManager* RM = ResourceManager::getInstance();

	GameObject* go = new GameObject();
	go->M_set_Texture(*(RM->getTexture("default")));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		go->M_draw(window);
		window.display();
	}

	return 0;
}
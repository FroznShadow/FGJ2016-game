#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"

class MenuState
	:public State
{
public:
	MenuState();
	~MenuState();
	void draw(sf::RenderWindow &window)override;
	void update(float dt)override;
private:
	float m_totalTime = 0;
	ResourceManager* m_RM;
	CircleButton* level0;
	CircleButton* level1;
	CircleButton* level2;
};

MenuState::MenuState()
{
	m_RM = ResourceManager::getInstance();
	m_RM->loadTexture("textures/Level0.bmp", "level0");
	m_RM->loadTexture("textures/Level0_pressed.bmp", "level0_p");
	m_RM->loadTexture("textures/Level1.bmp", "level1");
	m_RM->loadTexture("textures/Level1_pressed.bmp", "level1_p");

	level0 = new CircleButton(0, 0, 128);
	level0->M_set_Texture(*m_RM->getTexture("level0"));
	m_objects.push_back(level0);

	level1 = new CircleButton(0, 0, 128);
	level1->M_set_Texture(*m_RM->getTexture("level1"));
	m_objects.push_back(level1);

	level2 = new CircleButton(0, 0, 128);
	level2->M_set_Texture(*m_RM->getTexture("level1"));
	m_objects.push_back(level2);
}

MenuState::~MenuState()
{
	ResourceManager::getInstance()->clearAll();
}

void MenuState::update(const float dt)
{
	m_totalTime += dt;
	float pi = 3.1415926535;
	float range = 128 * sqrt(2);
	float centerX = 320 - 128;
	float centerY = 240 - 128;
	level2->M_set_Position(sf::Vector2f((cos(m_totalTime + 4 * pi / 3)) * range + centerX, (sin(m_totalTime + 4 * pi / 3)) * range + centerY));
	level1->M_set_Position(sf::Vector2f((cos(m_totalTime + 2 * pi / 3)) * range + centerX, (sin(m_totalTime + 2 * pi / 3)) * range + centerY));
	level0->M_set_Position(sf::Vector2f((cos(m_totalTime + 0 * pi / 3)) * range + centerX, (sin(m_totalTime + 0 * pi / 3)) * range + centerY));

	for (auto it : m_objects)
	{
		if (it == level0)
		{
			if (level0->isHovering())
			{
				level0->M_set_Texture(*m_RM->getTexture("level0_p"));
			}
			else
			{
				level0->M_set_Texture(*m_RM->getTexture("level0"));
			}
		}
		else if (it == level1)
		{
			if (level1->isHovering())
			{
				level1->M_set_Texture(*m_RM->getTexture("level1_p"));
			}
			else
			{
				level1->M_set_Texture(*m_RM->getTexture("level1"));
			}
		}
		else if (it == level2)
		{
			if (level2->isHovering())
			{
				level2->M_set_Texture(*m_RM->getTexture("level1_p"));
			}
			else
			{
				level2->M_set_Texture(*m_RM->getTexture("level1"));
			}
		}
	}
}

void MenuState::draw(sf::RenderWindow &window)
{
	//sf::Mouse::getPosition(window);


	for (auto it : m_objects)
	{
		it->M_draw(window);
	}
}

#endif
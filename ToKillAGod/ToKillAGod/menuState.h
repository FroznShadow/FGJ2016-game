#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.hpp"
#include "ResourceManager.h"

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
};

MenuState::MenuState()
{
	GameObject* level0 = new GameObject;
	level0->M_set_Texture(*ResourceManager::getInstance()->loadTexture("textures/Level0.bmp", "level0"));
	m_objects.push_back(level0);
}

MenuState::~MenuState()
{
	ResourceManager::getInstance()->clearAll();
}

void MenuState::update(const float dt)
{
	m_totalTime += dt;
	for (auto it : m_objects)
	{
		it->M_update(dt);
		it->M_set_Rotation(((sin(m_totalTime)/2+0.5)*360));
	}
}

void MenuState::draw(sf::RenderWindow &window)
{
	for (auto it : m_objects)
	{
		it->M_draw(window);
	}
}

#endif
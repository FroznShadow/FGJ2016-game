#pragma once

#include <vector>
#include "GameObject.h"
#include <SFML\Window.hpp>

class State
{
public:
	State();
	virtual ~State();
	virtual void update(const float dt)=0;
	virtual void draw(sf::RenderWindow &window)=0;
protected:
	std::vector<GameObject*> m_objects;
};

State::State() {}

State::~State() {}

void State::update(const float dt)
{
	for (auto it : m_objects)
	{
		it->M_update(dt);
	}
}

void State::draw(sf::RenderWindow &window)
{
	for (auto it : m_objects)
	{
		it->M_draw(window);
	}
}
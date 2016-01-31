#pragma once

#include <vector>
#include "GameObject.h"
#include <SFML\Window.hpp>

class StateManager;

class State
{
public:
	State(StateManager* manager);
	virtual ~State();
	virtual void update(const float dt)=0;
	virtual void draw(sf::RenderWindow &window)=0;
protected:
	std::vector<GameObject*> m_objects;
	std::vector<GameObject*> m_projectiles;
	StateManager* m_manager;
};

#include "StateManager.hpp"

State::State(StateManager* manager)
{
	m_manager = manager;
}

State::~State() {}

void State::update(const float dt)
{
	for (auto it : m_objects)
	{
		it->update(dt);
	}
}

void State::draw(sf::RenderWindow& window)
{
	for (auto it : m_objects)
	{
		it->draw(window);
	}
}
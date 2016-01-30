#pragma once

#include "State.hpp"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	State* getState();
	bool setState(State* state);

	void update(float dt);
	void draw(sf::RenderWindow & window);
private:
	State* m_currentState;
};

StateManager::StateManager() {}

StateManager::~StateManager() {}

State* StateManager::getState() {
	return m_currentState;
}

bool StateManager::setState(State* state) {
	if (m_currentState == state) {
		return false;
	}
	delete m_currentState;
	m_currentState = state;
	return true;
}

void StateManager::draw(sf::RenderWindow &window) {
	m_currentState->draw(window);
}

void StateManager::update(float deltaTime) {
	m_currentState->update(deltaTime);
}

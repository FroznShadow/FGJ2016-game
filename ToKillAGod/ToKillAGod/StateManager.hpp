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
	State* _currentState;
};

StateManager::StateManager() {}

StateManager::~StateManager() {}

State* StateManager::getState() {
	return _currentState;
}

bool StateManager::setState(State* state) {
	if (_currentState == state) {
		return false;
	}
	_currentState = state;
}

void StateManager::update(float dt) {
	_currentState->update(dt);
}

void StateManager::draw(sf::RenderWindow &window) {
	_currentState->draw(window);
}

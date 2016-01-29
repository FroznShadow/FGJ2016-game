#pragma once

#include <SFML\System.hpp>
#include "State.hpp"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	State* getState();
	bool setState(State* state);

	void update(float deltaTime);
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
	return true;
}

void StateManager::update(float deltaTime) {
	_currentState->update(deltaTime);
}
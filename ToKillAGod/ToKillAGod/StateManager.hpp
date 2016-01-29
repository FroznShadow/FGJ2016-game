#pragma once

#include "State.hpp"

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	State* getState();
	bool setState(State* state);

	void update();
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

void StateManager::update() {
	_currentState->update();
}
#pragma once

#include <iostream>
#include "State.hpp"

enum LevelFlag
{
    LEVEL_0_COMPLETED = 1,
    LEVEL_1_COMPLETED = 2,
    LEVEL_2_COMPLETED = 4,
    GAME_COMPLETED = 8,
};

class StateManager
{
public:
	StateManager();
	~StateManager();
	
	State* getState();
	bool setState(State* state);

	void update(float dt);
	void draw(sf::RenderWindow & window);
    void levelComplete(LevelFlag flag);
    bool isLevelCompleted(int levelNum)
    {
        return ((m_levelFlags >> levelNum) & 1) == 1;
    }
private:
	State* m_currentState;

    //game progress
    int m_levelFlags = 3;
    int m_difficulty = 0;
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
void StateManager::levelComplete(LevelFlag flag)
{
    m_levelFlags |= flag;
    std::cout << "flags: " << m_levelFlags << "\n";
}


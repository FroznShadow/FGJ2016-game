#pragma once

#include "GameObject.h"
#include "ResourceManager.h"

class �berEpicBoss : public GameObject
{
public:
	�berEpicBoss(float x, float y);
	~�berEpicBoss();

	void draw(sf::RenderWindow& window)override;
	void update(const float deltaTime)override;

	void move(float x, float y);
	void shoot(GameObject* target);
private:
	int m_hitpoints;
	float m_x;
	float m_y;

};

�berEpicBoss::�berEpicBoss(float x, float y) : m_x(x), m_y(y) {
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	setTexture(*RM->getTexture("BigBadBoss"));
}

�berEpicBoss::~�berEpicBoss()
{
}


void �berEpicBoss::draw(sf::RenderWindow& window) {

}

void �berEpicBoss::update(const float deltaTime) {

}

void �berEpicBoss::shoot(GameObject* target) {

}
#pragma once

#include "GameObject.h"
#include "ResourceManager.h"

class ÜberEpicBoss : public GameObject
{
public:
	ÜberEpicBoss(float x, float y);
	~ÜberEpicBoss();

	void draw(sf::RenderWindow& window)override;
	void update(const float deltaTime)override;

	void move(float x, float y);
	void shoot(GameObject* target);
private:
	int m_hitpoints;
	float m_x;
	float m_y;

};

ÜberEpicBoss::ÜberEpicBoss(float x, float y) : m_x(x), m_y(y) {
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	setTexture(*RM->getTexture("BigBadBoss"));
}

ÜberEpicBoss::~ÜberEpicBoss()
{
}


void ÜberEpicBoss::draw(sf::RenderWindow& window) {

}

void ÜberEpicBoss::update(const float deltaTime) {

}

void ÜberEpicBoss::shoot(GameObject* target) {

}
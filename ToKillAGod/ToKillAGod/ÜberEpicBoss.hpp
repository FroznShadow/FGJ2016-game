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
private:
	int m_hitpoints;
	float m_x;
	float m_y;
	bool m_turn;
	float m_z;
};

ÜberEpicBoss::ÜberEpicBoss(float x, float y) : m_x(x), m_y(y), m_z(x), m_turn(false) {
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	setTexture(*RM->getTexture("BigBadBoss"));
	m_sprite.setOrigin(64, 64);
}

ÜberEpicBoss::~ÜberEpicBoss()
{}


void ÜberEpicBoss::draw(sf::RenderWindow& window) {
	GameObject::draw(window);
}

void ÜberEpicBoss::update(const float deltaTime) {
	m_z += 75 * deltaTime;
	m_x = (500 * sinf(m_z * 2 * 3.14159265359f / 180))/2;
	m_y = 50 * sinf(m_z * 3 * 3.14159265359f / 180) -412;

	setPosition(sf::Vector2f(m_x, m_y));
}
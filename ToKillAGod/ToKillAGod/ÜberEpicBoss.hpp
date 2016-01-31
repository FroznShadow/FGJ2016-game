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
	float& hp() { return m_hitpoints; }
private:
	float m_hitpoints;
	float m_x;
	float m_y;
	float m_z;
	sf::Texture m_tex;
};

ÜberEpicBoss::ÜberEpicBoss(float x, float y) : m_x(x), m_y(y), m_z(x), m_hitpoints(9999999999.9f) {
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	m_tex = *RM->getTexture("BigBadBoss");
	m_tex.setSmooth(true);
	setTexture(m_tex);
	m_sprite.setOrigin(281, 281);
	m_sprite.setScale(0.75, 0.75);
}

ÜberEpicBoss::~ÜberEpicBoss()
{}


void ÜberEpicBoss::draw(sf::RenderWindow& window) {
	GameObject::draw(window);
}

void ÜberEpicBoss::update(const float deltaTime) {
	m_z += 15 * deltaTime;
	m_x = (500 * sinf(m_z * 2 * 3.14159265359f / 180))/2;
	m_y = 50 * sinf(m_z * 3 * 3.14159265359f / 180) - 525;

	setPosition(sf::Vector2f(m_x, m_y));
}
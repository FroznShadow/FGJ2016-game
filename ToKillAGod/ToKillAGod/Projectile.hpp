#pragma once

#include "GameObject.h"
#include "ResourceManager.h"

class Projectile : public GameObject
{
public:
	Projectile(float x, float y, float xTarget, float yTarget);
	~Projectile();

	void draw(sf::RenderWindow& window)override;
	void update(const float deltaTime)override;
private:
	float m_xTarget;
	float m_yTarget;
	float m_x;
	float m_y;
};

Projectile::Projectile(float x, float y, float xTarget, float yTarget)
	:m_x(x), m_y(y), m_xTarget(xTarget), m_yTarget(yTarget)
{
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	setTexture(*RM->getTexture("Projectile1"));
}

Projectile::~Projectile()
{}

void Projectile::draw(sf::RenderWindow& window) {
	GameObject::draw(window);
}

void Projectile::update(const float deltaTime) {
	//move towards target or some shit
}
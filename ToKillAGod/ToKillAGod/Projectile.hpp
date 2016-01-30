#pragma once

#include "GameObject.h"
#include "ResourceManager.h"
#include "ParticleManager.h"

class Projectile : public GameObject
{
public:
	Projectile(float x, float y, float xTarget, float yTarget);
	~Projectile();

	void draw(sf::RenderWindow& window)override;
	void update(const float deltaTime)override;

    float getX(){ return m_x; }
    float getY(){ return m_y; }
private:
	float m_xTarget;
	float m_yTarget;
	float m_x;
	float m_y;
    float m_vspeed;
    float m_hspeed;
};

Projectile::Projectile(float x, float y, float xTarget, float yTarget)
	:m_x(x), m_y(y), m_xTarget(xTarget), m_yTarget(yTarget)
{
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(sf::Vector2f(m_x, m_y));

	setTexture(*RM->getTexture("Projectile1"));

    float speed = 15;
    float direction = (float)(rand() % 180) * 3.14159265 / 180;
    m_hspeed = cos(direction) * speed;
    m_vspeed = -sin(direction) * speed;
}

Projectile::~Projectile()
{}

void Projectile::draw(sf::RenderWindow& window) {
	GameObject::draw(window);
}

void Projectile::update(const float deltaTime) {
	//move towards target or some shit
    float a = 5.0f * deltaTime;
    float dir = atan2f(m_yTarget - m_y, m_xTarget - m_x);
    m_hspeed += cos(dir) * a;
    m_vspeed += sin(dir) * a;

    float tot_speed = sqrt(m_hspeed*m_hspeed + m_vspeed*m_vspeed);
    if (tot_speed > 30.0f || (abs(m_x + m_hspeed - m_xTarget) > abs(m_x - m_xTarget) && (abs(m_x + m_hspeed - m_xTarget) > abs(m_x - m_xTarget))))
    {
        m_hspeed *= (1.0f - deltaTime);
        m_vspeed *= (1.0f - deltaTime);
    }
    
    m_x += m_hspeed;
    m_y += m_vspeed;

    setPosition(sf::Vector2f(m_x-64.0f, m_y-64.0f));
}
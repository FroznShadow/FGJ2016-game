#include "Player.h"

Player::Player(sf::Vector2f position)
	: m_hitPoints(1), m_life(3), m_position(position), m_maxSpeed(25), m_velocity(sf::Vector2f(0.5f,0.5f))
{
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(m_position);
}

Player::~Player()
{}

void Player::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}

void Player::update(float deltaTime)
{
}
void Player::jump(float jumpSpeed)
{
	m_velocity.y += jumpSpeed;
}

void Player::move(float dx, float dy)
{
	m_position.x += dx;
	m_position.y += dy;
	setPosition(m_position);
}

void Player::hit(int dmg) {
	m_hitPoints -= dmg;
}
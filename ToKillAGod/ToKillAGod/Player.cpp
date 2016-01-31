#include "Player.h"

Player::Player(sf::Vector2f position)
	: m_HP(100.0f), m_maxHP(m_HP), m_position(position), m_maxSpeed(25), m_velocity(sf::Vector2f(0.5f, 0.5f))
{
	m_hpBar = nullptr;
	ResourceManager* RM = ResourceManager::getInstance();
	setPosition(m_position);
}

Player::~Player()
{}

void Player::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}

void Player::drawHP(sf::RenderWindow& window) {
	if (m_hpBar != nullptr) {
		m_hpBar->setScale(m_HP / m_maxHP, 1);
		window.draw(*m_hpBar);
	}
}

void Player::update(float deltaTime) {
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

void Player::hit(float dmg) {
	m_HP -= dmg;
}

void Player::initHP(sf::Vector3f color, float size) {
	m_hpBar = new sf::RectangleShape(sf::Vector2f(size, 50));
	m_hpBar->setFillColor(sf::Color(color.x, color.y, color.z, 255));
	m_hpBar->setOrigin(size/2, 25);
}

void Player::setHPPosition(sf::Vector2f pos) {
	m_hpBar->setPosition(pos);
}
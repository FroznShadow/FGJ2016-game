#include "Player.h"

Player::Player(sf::Vector2f position)
	: m_HP(100.0f), m_maxHP(m_HP), m_alpha(0.0f), m_position(position), m_maxSpeed(25), m_velocity(sf::Vector2f(0.5f, 0.5f))
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
	if (m_hpBar != nullptr) {
		if (m_alpha < 255.0f) {
			m_hpBar->setFillColor(sf::Color(m_hpBar->getFillColor().r, m_hpBar->getFillColor().g, m_hpBar->getFillColor().b, m_alpha));
		}
		m_hpBar->setScale(m_HP / m_maxHP, 50);
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

void Player::hit(int dmg) {
	m_HP -= dmg;
}

void Player::initHP(sf::Vector3f color, float size) {
	m_hpBar = new sf::RectangleShape(sf::Vector2f(size, 50));
	m_hpBar->setFillColor(sf::Color(color.x, color.y, color.z, m_alpha));
	m_hpBar->setOrigin(size/2, 25);
}

void Player::setHPPosition(sf::Vector2f pos) {
	m_hpBar->setPosition(pos);
}
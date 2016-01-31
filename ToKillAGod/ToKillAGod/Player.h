#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"
#include "ResourceManager.h"

class Player : public GameObject
{
public:
	Player(sf::Vector2f position);
	~Player();
	void draw(sf::RenderWindow& window)override;
    void update(const float deltaTime)override;
	void jump(float jumpSpeed);
	void move(float dx, float dy);
	sf::Vector2f getVelocity() { return m_velocity; }
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; }
	void hit(int dmg);
	void Player::initHP(sf::Vector3f color, float size);
	void setHPPosition(sf::Vector2f pos);
	sf::Vector2f getHPPos() { return m_hpBar->getPosition(); }
	float& getHSpeed() { return m_hSpeed; }
	float& getVSpeed() { return m_vSpeed; }
	float& hp() { return m_HP; }
	float& alpha() { return m_alpha; }
private:
	float m_HP;
	float m_maxHP;
	float m_alpha;
	sf::Vector2f m_position;
	float m_maxSpeed;
	sf::Vector2f m_velocity;
	float m_hSpeed;
	float m_vSpeed;
};

#endif // !PLAYER_H

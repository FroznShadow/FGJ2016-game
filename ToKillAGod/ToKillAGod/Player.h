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
	void update(float deltaTime)override;
	void jump(float jumpSpeed);

	sf::Vector2f getVelocity() { return m_velocity; }
private:
	int m_hitPoints;
	int m_life;
	sf::Vector2f m_position;
	float m_maxSpeed;
	sf::Vector2f m_velocity;

};

#endif // !PLAYER_H

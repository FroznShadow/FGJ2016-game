#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void draw();
	void movePlayer(std::string dir);
	//void collision();
	void jump();
private:
	int m_hitPoints;
	sf::Vector2f m_position;
	float m_acceleration;
	float m_deceleration;
	float m_maxSpeed;
	float m_jumpAcceleration;
	float m_xVelocity;
	float m_yVelocity;
};

#endif // !PLAYER_H

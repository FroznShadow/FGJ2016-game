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
	int hitPoints;
	sf::Vector2f position;
	float acceleration;
	float deceleration;
	float max_speed;
	float jump_Acceleration;
	float x_velocity;
	float y_velocity;
};

#endif // !PLAYER_H

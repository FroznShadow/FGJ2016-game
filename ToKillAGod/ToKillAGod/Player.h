#ifndef PLAYER_H
#define PLAYER_H
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void update();
	void movePlayer();

private:
	int hitPoints;
	sf::Vector2f position;
};

#endif // !PLAYER_H

#include "Player.h"

Player::Player()
{
	this->M_set_Position(position);
}

Player::~Player()
{

}

void Player::draw()
{
	//draw (sprite);
}
void Player::movePlayer(std::string dir)
{
	if (x_velocity < max_speed && x_velocity >-max_speed)
	{
		if (dir == "right")
		{
			x_velocity += acceleration;
		}
		else if (dir == "left");
		{
			x_velocity -= acceleration;
		}
	}
	else
		return;
}
void Player::jump()
{
	y_velocity += jump_Acceleration;
}
//void collision()
//{
//	//get rect noob
//}

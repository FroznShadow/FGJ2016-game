#include "Player.h"

Player::Player()
{
	//this->setPosition(m_position);
}

Player::~Player()
{}

void Player::draw()
{
	//draw (sprite);
}
void Player::movePlayer(std::string dir)
{
	if (m_xVelocity < m_maxSpeed && m_xVelocity > -m_maxSpeed)
	{
		if (dir == "right")
		{
			m_xVelocity += m_acceleration;
		}
		else if (dir == "left");
		{
			m_xVelocity -= m_acceleration;
		}
	}
	else
		return;
}
void Player::jump()
{
	m_yVelocity += m_jumpAcceleration;
}
//void collision()
//{
//	//get rect noob
//}

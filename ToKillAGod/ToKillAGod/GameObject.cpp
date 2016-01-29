#include "GameObject.h"

GameObject::GameObject(sf::Vector2f position) 
{

}

GameObject::~GameObject()
{

}
void GameObject::M_draw(sf::RenderWindow& window)
{

	window.draw(P_sprite);
}


//------------//
// Set Values //
//------------//
void GameObject::M_set_Position(const sf::Vector2f& value)
{
	P_sprite.setPosition(value - P_origin);
}
void GameObject::M_set_Texture(const sf::Texture& value)
{
	P_sprite.setTexture(value);
}
void GameObject::M_set_Texture_Rectangle(const sf::IntRect& value)
{
	P_sprite.setTextureRect(value);
	P_origin.x = 0.5f * value.width;
	P_origin.y = 0.5f * value.height;
	P_sprite.setOrigin(P_origin);
}
void GameObject::M_set_Rotation(float value)
{
	float erotus = (value - this->M_get_Rotation());
	if (erotus < 0)
		erotus += 360;
	if (erotus > 0 && erotus < 180)
	{
		if (erotus >35 && erotus < 145)
			P_sprite.rotate(0.2);
		P_sprite.rotate(0.1);
	}

	else if (erotus < 359 && erotus > 180)
	{
		if (erotus >215 && erotus < 325)
			P_sprite.rotate(-0.2);
		P_sprite.rotate(-0.1);
	}
}


//------------//
// Get Values //
//------------//
sf::Vector2f GameObject::M_get_position() const
{
	return P_sprite.getPosition() + P_origin;
}
float GameObject::M_get_Rotation() const
{
	return P_sprite.getRotation();
}
sf::FloatRect GameObject::M_get_Bounding_Box() const
{
	return P_sprite.getGlobalBounds();
}

void GameObject::M_update_Origin()
{
	P_origin.x = 0.5f * P_sprite.getTexture()->getSize().x;
	P_origin.y = 0.5f * P_sprite.getTexture()->getSize().y;
}
void GameObject::M_Rotation(float value)
{
	P_sprite.rotate(value);
}

void GameObject::M_Destroy()
{
	delete this;
}
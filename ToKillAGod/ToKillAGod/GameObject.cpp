#include "GameObject.h"

GameObject::GameObject(sf::Vector2f position, TYPE type)
	:m_type(type)
{
	setPosition(position);
}

GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow& window)
{

	window.draw(m_sprite);
}

void GameObject::update(const float dt)
{
	
}

//------------//
// Set Values //
//------------//
void GameObject::setPosition(const sf::Vector2f& value)
{
	m_sprite.setPosition(value - m_origin);
}
void GameObject::setTexture(const sf::Texture& value)
{
	m_sprite.setTexture(value);
}
void GameObject::setTextureRectangle(const sf::IntRect& value)
{
	m_sprite.setTextureRect(value);
	m_origin.x = 0.5f * value.width;
	m_origin.y = 0.5f * value.height;
	m_sprite.setOrigin(m_origin);
}
void GameObject::setRotation(float value)
{
	float erotus = (value - this->getRotation());
	if (erotus < 0)
		erotus += 360;
	if (erotus > 0 && erotus < 180)
	{
		if (erotus >35 && erotus < 145)
			m_sprite.rotate(0.2);
		m_sprite.rotate(0.1);
	}

	else if (erotus < 359 && erotus > 180)
	{
		if (erotus >215 && erotus < 325)
			m_sprite.rotate(-0.2);
		m_sprite.rotate(-0.1);
	}
}
void GameObject::setType(TYPE type)
{
	m_type = type;
}


//------------//
// Get Values //
//------------//
sf::Vector2f GameObject::getPosition() const
{
	return m_sprite.getPosition() + m_origin;
}
float GameObject::getRotation() const
{
	return m_sprite.getRotation();
}
sf::FloatRect GameObject::getBoundingBox() const
{
	return m_sprite.getGlobalBounds();
}
TYPE GameObject::getType()const
{
	return m_type;
}



//??


void GameObject::updateOrigin()
{
	m_origin.x = 0.5f * m_sprite.getTexture()->getSize().x;
	m_origin.y = 0.5f * m_sprite.getTexture()->getSize().y;
}
void GameObject::rotation(float value)
{
	m_sprite.rotate(value);
}

void GameObject::destroy()
{
	delete this;
}

void GameObject::circleCollision(GameObject* go) {
	float radius = ((this->m_sprite.getLocalBounds().width / 2) + (this->m_sprite.getLocalBounds().height / 2) / 2);
	float radius2 = ((go->m_sprite.getLocalBounds().width / 2) + (go->m_sprite.getLocalBounds().height / 2) / 2);

	if (((this->m_sprite.getPosition().x - go->m_sprite.getPosition().x)*(this->m_sprite.getPosition().x - go->m_sprite.getPosition().x))
		+ ((this->m_sprite.getPosition().y - go->m_sprite.getPosition().y)*(this->m_sprite.getPosition().y - go->m_sprite.getPosition().y))
		<= (radius + radius2)*(radius + radius2)) {
		//gollide
	}
}
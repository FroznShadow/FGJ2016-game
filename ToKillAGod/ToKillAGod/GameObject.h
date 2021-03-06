#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
enum TYPE
{

	TILE,
	PLAYER,
	ENEMY,
	OBJECTIVE,
};
class GameObject
{
public:
	GameObject(sf::Vector2f position, TYPE type = TILE);
	GameObject(){}
	~GameObject();

	//Set values//
	void destroy();
	void setPosition(const sf::Vector2f& value);
	void setTexture(const sf::Texture& value);
	void setTextureRectangle(const sf::IntRect& value);
	void setRotation(float value);
	void setType(TYPE type);

	//GetValues//
	sf::Vector2f	getPosition() const;
	float			getRotation() const;
	sf::FloatRect	getBoundingBox() const;
	TYPE			getType() const;
	sf::Sprite&		getSprite() { return m_sprite; }
    bool            isDestroyed() { return m_isRemoved; }


	//Other values//
	void rotation(float value);
	virtual void draw(sf::RenderWindow& window)=0;
	virtual void update(const float dt)=0;
	GameObject* circleCollision(GameObject* go);
    void updateOrigin();

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_origin;
	TYPE m_type;
	sf::RectangleShape* m_hpBar;
    bool m_isRemoved;
};


#endif // !GAMEOBJECT_H

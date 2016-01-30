#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
enum TYPE
{
	TILE,
	PLAYER,
	ENEMY
};
class GameObject
{
public:
	GameObject(sf::Vector2f position, TYPE type = TILE);
	GameObject(){}
	~GameObject();

	//Set values//
	void Destroy();
	void M_set_Position(const sf::Vector2f& value);
	void M_set_Texture(const sf::Texture& value);
	void M_set_Texture_Rectangle(const sf::IntRect& value);
	void M_set_Rotation(float value);
	void M_set_Type(TYPE type);

	//GetValues//
	sf::Vector2f	M_get_position() const;
	float			M_get_Rotation() const;
	sf::FloatRect	M_get_Bounding_Box() const;
	TYPE			M_get_Type() const;

	//Other values//
	void M_Rotation(float value);
	void M_Destroy();
	virtual void M_draw(sf::RenderWindow& window)=0;
	virtual void M_update(const float dt)=0;

protected:
	
	sf::Sprite P_sprite;
	sf::Vector2f P_origin;
	void M_update_Origin();
	TYPE M_type;
};


#endif // !GAMEOBJECT_H

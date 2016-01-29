#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML\Main.hpp"
#include "SFML\Graphics.hpp"
enum TYPE
{
	Tile,
	Player,
	Enemy
};
class GameObject
{
public:
	GameObject(sf::Vector2f position);
	GameObject(){}
	~GameObject();

	//Set values//
	void Destroy();
	void M_set_Position(const sf::Vector2f& value);
	void M_set_Texture(const sf::Texture& value);
	void M_set_Texture_Rectangle(const sf::IntRect& value);
	void M_set_Rotation(float value);

	//GetValues//
	sf::Vector2f	M_get_position() const;
	float			M_get_Rotation() const;
	sf::FloatRect	M_get_Bounding_Box() const;

	//Other values//
	void M_Rotation(float value);
	void M_Destroy();
	void M_draw(sf::RenderWindow& window);
	void M_update(const float dt);

protected:
	
	sf::Sprite P_sprite;
	sf::Vector2f P_origin;
	void M_update_Origin();
};


#endif // !GAMEOBJECT_H

#ifndef TILE_H
#define TILE_H
#include "GameObject.h"

class Tile : public GameObject
{
public:
	/*
	* Normal = just floor
	* Danger = makes damage
	* Heal = heals?
	*/
	enum TileType
	{
		normal,
		danger,
		heal,
		background,
		bouncer,
		objective
	};

	Tile();
	Tile(float x, float y, TileType type);
	~Tile(){};
	void M_draw(sf::RenderWindow &window)override{ GameObject::M_draw(window); }
	void M_update(float dt)override{ GameObject::M_update(dt); }

	TileType getType(){ return m_tileType; }

private:
	TileType m_tileType;
};

#endif
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
		bouncer,
		objective,
        checkpoint
	};

	Tile();
	Tile(float x, float y, TileType type);
	~Tile(){};
	void draw(sf::RenderWindow &window)override{ GameObject::draw(window); }
    void update(const float dt)override{ GameObject::update(dt); }

    void setTileType(TileType type){ m_tileType = type; }
	TileType getTileType(){ return m_tileType; }

private:
	TileType m_tileType;
};

#endif
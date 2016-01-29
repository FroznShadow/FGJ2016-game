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
	enum Types
	{
		normal,
		danger,
		heal,
		background,
		bouncer,
		objective
	};

	Tile();
	Tile(Types);
	~Tile();

	std::string getType();

private:
	Types tileType;
};

Tile::Tile()
{
}

Tile::~Tile()
{
}

#endif
#include "Tile.h"
#include "ResourceManager.h"

/// Public 
Tile::Tile(Types type)
{
	//TODO: load tile textures @ game state
	ResourceManager* RM = ResourceManager::getInstance();
	tileType = type;
	switch (tileType)
	{
	case Types::normal:
		M_set_Texture(*RM->getTexture("tile"));
		// Set texture to normal tile
		break;
	case Types::danger:
		// Set texture to danger tile
		break;
	case Types::heal:
		// Set texture to heal tile
		break;
	default:
		// Set texture to normal tile just in case
		printf("Error when setting tiletype. In Tile.cpp");
		break;
	}
}
#include "Tile.h"
#include "ResourceManager.h"

/// Public 
Tile::Tile(float x, float y, TileType type)
	:GameObject(sf::Vector2f(x, y), TYPE::TILE)
{
	//TODO: load tile textures @ game state
	ResourceManager* RM = ResourceManager::getInstance();
	m_tileType = type;
	switch (m_tileType)
	{
	case TileType::normal:
		M_set_Texture(*RM->getTexture("normal"));
		break;
	case TileType::danger:
		M_set_Texture(*RM->getTexture("danger"));
		break;
	case TileType::heal:
		M_set_Texture(*RM->getTexture("heal"));
		break;
	case TileType::background:
		M_set_Texture(*RM->getTexture("background"));
		break;
	case TileType::bouncer:
		M_set_Texture(*RM->getTexture("bouncer"));
		break;
	case TileType::objective:
		M_set_Texture(*RM->getTexture("objective"));
		break;
	default:
		// Set texture to normal tile just in case
		printf("Error when setting tiletype. In Tile.cpp");
		break;
	}
}
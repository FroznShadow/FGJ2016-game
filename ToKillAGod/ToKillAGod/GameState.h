#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"

class StateManager;

class GameState
	:public State
{
public:
	GameState(StateManager* manager);
	~GameState();
	void draw(sf::RenderWindow &window)override;
	void update(float dt)override;
private:

	void addTile(Tile::TileType type, float x, float y);
	void generate();

	ResourceManager* m_RM;
};

void GameState::addTile(Tile::TileType type, float x, float y)
{
	m_objects.push_back(new Tile((x+16) * 64, y * 32, type));
}

GameState::GameState(StateManager* manager)
	:State(manager)
{
	m_RM = ResourceManager::getInstance();
	m_RM->loadTexture("textures/tile_cyan.png", "normal");
	m_RM->loadTexture("textures/tile_cyan.png", "danger");
	m_RM->loadTexture("textures/tile_cyan.png", "heal");
	m_RM->loadTexture("textures/tile_red.png", "background");
	m_RM->loadTexture("textures/tile_chess.png", "bouncer");
	m_RM->loadTexture("textures/tile_objective.png", "objective");

	generate();
}

GameState::~GameState()
{
	ResourceManager::getInstance()->clearAll();
}

void GameState::generate()
{
	//generate starting platform
	for (unsigned j = 0; j < 16; j++)
	{
		addTile(Tile::TileType::background, j - 15.0f, 4);
	}

	//set seed
	srand(time(NULL));

	int levelHeight = 4; //height of the "possible" platform
	int gapWidth = 0;    //obstacle width [0...3]
	int heightLength = 0;//length of the platform that has been generated on the current height
	int totalLength = 0;
	bool bouncerGap = false;
	//generate level
	float levelLength = 200;
	for (unsigned i = 0; i < levelLength; i++)
	{
		if (gapWidth > 0)
		{
			if (gapWidth >(bouncerGap ? 5 : 3))
			{
				gapWidth = 0;
				addTile(Tile::TileType::normal, i, levelHeight);
			}
			else
			{
				gapWidth++;
			}
		}
		else
		{
			if (rand() % 4 == 0 && heightLength > 1)
			{
				//start a gap
				bouncerGap = false;
				gapWidth++;
				if (rand() % 4 == 0)
				{
					addTile(Tile::TileType::bouncer, i, levelHeight);
				}
			}
			else
			{
				if (heightLength > 2)
				{
					if (rand() % 3 == 0)
					{
						//change the height of the possible level
						levelHeight += (rand() % 5) - 2;
						heightLength = 0;
					}
				}
				addTile(Tile::TileType::normal, i, levelHeight);
				heightLength++;
			}
		}
		if (totalLength == levelLength-1)
		{
			addTile(Tile::TileType::objective, i-1, levelHeight-1);
		}
		totalLength++;
	}
}

void GameState::update(const float dt)
{
	for (auto it : m_objects)
	{
		it->setPosition(sf::Vector2f(it->getPosition().x - dt * 800, it->getPosition().y));
	}
}

void GameState::draw(sf::RenderWindow &window)
{
	//sf::Mouse::getPosition(window);


	for (auto it : m_objects)
	{
		it->draw(window);
	}
}

#endif
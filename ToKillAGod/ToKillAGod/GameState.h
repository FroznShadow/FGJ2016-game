#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"
#include "Player.h"

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
	GameObject* getPlayerCollision();
	void movePlayer();
	ResourceManager* m_RM;
	Player* m_player;
};

void GameState::addTile(Tile::TileType type, float x, float y)
{
	m_objects.push_back(new Tile((x+16) * 128, y * 128, type));
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
	m_RM->loadTexture("textures/player.png", "wizard");

	//m_player = new Player();

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
		//it->setPosition(sf::Vector2f(it->getPosition().x - dt * 50, it->getPosition().y));
	}

	movePlayer();
}

void GameState::draw(sf::RenderWindow &window)
{
	//sf::Mouse::getPosition(window);
	sf::View playerView(m_player->getPosition(), (sf::Vector2f)window.getSize());

	window.setView(playerView);

	for (auto it : m_objects)
	{
		it->draw(window);
	}
}

void GameState::movePlayer()
{
	float hspeed = 0, vspeed = 0;
	sf::Vector2f pos = m_player->getPosition();
	sf::Vector2f prev = m_player->getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		hspeed += 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_player->setPosition(sf::Vector2f(m_player->getPosition().x + 1, m_player->getPosition().y));
		if (getPlayerCollision() == nullptr)
		{
			vspeed = -10;
		}
		m_player->setPosition(prev);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		hspeed -= 5;

	vspeed += m_player->getVelocity().x;

	//deprecated useless trigonometry. please, don't look.
	/*if (hspeed == 0 && vspeed == 0)
	{
		speed = 0;
	}
	else
	{
		speed = sqrt(vspeed*vspeed + hspeed*hspeed);
	}*/

	//direction = atan2f(vspeed, hspeed);

	//liikkuminen x-akselilla
	pos.x += hspeed;
	m_player->setPosition(pos);
	GameObject* other = getPlayerCollision();
	if (other != nullptr)
	{
		//jos pelaaja törmää, siirretään pelaajaa seinän viereen
		if (pos.x > other->getPosition().x)
		{
			m_player->setPosition(sf::Vector2f(other->getPosition().x + 128.0f, pos.y));
		}
		else
		{
			m_player->setPosition(sf::Vector2f(other->getPosition().x - 128.0f, pos.y));
		}
		hspeed = 0;
	}
	//liikkuminen y-akselilla
	pos = m_player->getPosition();
	prev = pos;
	pos.y += m_player->getVelocity().y;
	m_player->setPosition(pos);
	other = getPlayerCollision();
	if (other != nullptr)
	{
		if (pos.y > other->getPosition().y)
		{
			m_player->setPosition(sf::Vector2f(pos.x, other->getPosition().y + 128.0f));
		}
		else
		{
			m_player->setPosition(sf::Vector2f(pos.x, other->getPosition().y - 128.0f));
		}
		vspeed = 0;
	}
	else
	{
		prev = m_player->getPosition();
		if (getPlayerCollision() != nullptr)
		{
			m_player->setPosition(prev);
		}
		else
		{
			vspeed += 0.5;
			if (vspeed > 100)
				vspeed = 100;
		}
	}

	if (m_player->getPosition().y > 10000)
	{
		m_player->destroy();
	}

	m_player->setVelocity(sf::Vector2f(vspeed, hspeed));
}

GameObject* GameState::getPlayerCollision()
{
	for (GameObject* it : m_objects)
	{
		if (it != m_player && it->getType() == TYPE::TILE)
		{
			sf::Vector2f position = m_player->getPosition();
			sf::FloatRect size = m_player->getBoundingBox();
			if (position.x + size.width > it->getPosition().x &&
				position.y + size.height > it->getPosition().y &&
				position.x < it->getPosition().x + 128.0f &&
				position.y < it->getPosition().y + 128.0f
				)
			{
				return it;
			}
		}
	}
	return nullptr;
}

#endif
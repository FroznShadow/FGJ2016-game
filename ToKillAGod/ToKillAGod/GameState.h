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
	void levelFinish();
	GameObject* getPlayerCollision();
	void movePlayer(float dt);
	ResourceManager* m_RM;
	bool objective = false;
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

	generate();
}

GameState::~GameState()
{
	ResourceManager::getInstance()->clearAll();
}

void GameState::generate()
{
	std::cout << "asd";

	m_player = new Player(sf::Vector2f(256, 256));
	m_player->setVelocity(sf::Vector2f(0, 0));
	m_player->setTexture(*m_RM->getTexture("wizard"));
	m_objects.push_back(m_player);


	addTile(Tile::TileType::normal, 1, 1);
	addTile(Tile::TileType::normal, 2, 1);

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
	float levelLength = 50;
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
		if (totalLength == levelLength-1 && !objective)
		{			
			if (objective == false) {
				objective = true;
				std::cout << objective << std::endl;
				totalLength++;
				addTile(Tile::TileType::objective, i - 1, levelHeight - 1);
				return;
			}
		}
		else {
			totalLength++;
		}

	}
}

void GameState::update(const float dt)
{
	movePlayer(dt);
}

void GameState::draw(sf::RenderWindow &window)
{
	//sf::Mouse::getPosition(window);
	sf::View playerView(m_player->getPosition(), (sf::Vector2f)window.getSize()*2.0f);

	window.setView(playerView);

	for (auto it : m_objects)
	{
		it->draw(window);
	}
}

void GameState::movePlayer(float dt)
{
	sf::Vector2f prev = m_player->getPosition();
	float hspeed = 0.0f;
	float vspeed = m_player->getVelocity().y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		hspeed += 1000*dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		hspeed -= 1000*dt;
	
	//check if can fall
	m_player->move(0, 1);
	if (!getPlayerCollision()) //fall or move back
	{
		vspeed += 15 * dt;
	}
	else
	{
		vspeed = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			vspeed = -15.0f;
	}
	m_player->move(0, -1);

	//try to move
	GameObject* other = nullptr;

	//x
	m_player->move(hspeed, 0);
	other = getPlayerCollision();
	if (other)
	{
		//move next to the wall
		float dx = other->getPosition().x - m_player->getPosition().x; //gap between the player and the wall
		m_player->move(((dx > 0) ? ( - m_player->getBoundingBox().width ) : 128.0) + dx, 0);
		hspeed = 0;
	}
	m_player->move(0, vspeed);
	other = getPlayerCollision();
	if (other)
	{
		//move next to the wall
		float dy = other->getPosition().y - m_player->getPosition().y; //gap between the player and the wall
		m_player->move(0, dy + ((dy > 0) ? -m_player->getBoundingBox().height : 128.0f));
		vspeed = 0;
	}

	m_player->setVelocity(sf::Vector2f(hspeed, vspeed));

	if (m_player->getPosition().y > 10000)
	{
		//m_player->destroy();
		std::cout << "haha kuolit!";
		sf::Vector2f pos = m_player->getPosition();
		m_player->move(-pos.x + 256, -pos.y);
		m_player->setVelocity(sf::Vector2f());
	}
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
				if (dynamic_cast<Tile*>(it)->getTileType() == Tile::TileType::objective)
				{
					std::cout << "Level finished\n";
					levelFinish();
				}
				return it;
			}
		}

	}
	return nullptr;
}
void GameState::levelFinish()
{

	m_manager->setState(new MenuState(m_manager));
}

#endif
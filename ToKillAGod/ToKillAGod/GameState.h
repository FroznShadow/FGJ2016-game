#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"
#include "Player.h"
#include <SFML\Audio.hpp>
class StateManager;

class GameState
	:public State
{
public:
	GameState(StateManager* manager, int level);
	~GameState();
	void draw(sf::RenderWindow &window)override;
    void update(const float dt)override;
private:
	void addTile(Tile::TileType type, float x, float y);
	void generate();
	void levelFinish();
	GameObject* getPlayerCollision();
	void movePlayer(float dt);
	ResourceManager* m_RM;
	bool objective = false;
	bool finished = false;
	Player* m_player;
    int m_level;
	sf::Sprite sprite;
	sf::Texture texture;

	sf::SoundBuffer fallbuffer;
	sf::SoundBuffer finishbuffer;
	sf::SoundBuffer jumpbuffer;
	sf::SoundBuffer checkpointbuffer;

	sf::Sound fall;
	sf::Sound finish;
	sf::Sound jump;
	sf::Sound checkpoint;

    sf::Vector2f m_checkpoint;

	int kakkaa; //ehh... difficulty modifier?
};

void GameState::addTile(Tile::TileType type, float x, float y)
{
	m_objects.push_back(new Tile((x+16) * 128, y * 128, type));
	
	//if (type == Tile::TileType::danger) {
	//	m_objects[m_objects.size()-1]->getSprite().setOrigin(64, 64);
	//	//m_objects[m_objects.size() - 1]->getSprite().setPosition();
	//}
}


GameState::GameState(StateManager* manager, int level)
    :State(manager), m_level(level)
{
	kakkaa = manager->getModifier();
	m_RM = ResourceManager::getInstance();
	m_RM->loadTexture("textures/danger.png", "danger");
	//m_RM->loadTexture("textures/tile_cyan.png", "heal");
	m_RM->loadTexture("textures/tile_bouncer.png", "checkpoint");
	m_RM->loadTexture("textures/tile_chess.png", "bouncer");
	m_RM->loadTexture("textures/tile_objective.png", "objective");
	texture.loadFromFile("textures/background.png");
	//sprite.setPosition(m_player->getPosition());
	sprite.setTexture(texture);
	sprite.setScale(4, 3);
    switch (level)
    {

	case 0:
	{
		m_RM->loadTexture("textures/Player_blue.png", "wizard");
		m_RM->loadTexture("textures/tile_cyan.png", "normal");
		break;
	}
	case 1:
	{
		m_RM->loadTexture("textures/Player_red.png", "wizard");
		m_RM->loadTexture("textures/tile_red.png", "normal");
	}
	case 2:
	{
		m_RM->loadTexture("textures/Player_white.png", "wizard");
		m_RM->loadTexture("textures/tile_white.png", "normal");
	}

    }

	generate();
	fallbuffer.loadFromFile("audio/falldown.wav");
	jumpbuffer.loadFromFile("audio/jump.wav");
	finishbuffer.loadFromFile("audio/finishStage.wav");
	checkpointbuffer.loadFromFile("audio/steponcheckpoint.wav");

	fall.setBuffer(fallbuffer);
	jump.setBuffer(jumpbuffer);
	finish.setBuffer(finishbuffer);
	checkpoint.setBuffer(checkpointbuffer);

    m_player->setTexture(*m_RM->getTexture("wizard"));
}

GameState::~GameState()
{
	m_RM->deleteTexture("normal");
	m_RM->deleteTexture("danger");
	m_RM->deleteTexture("heal");
	m_RM->deleteTexture("background");
	m_RM->deleteTexture("bouncer");
	m_RM->deleteTexture("objective");
	m_RM->deleteTexture("wizard");
	std::cout << "destruction" << std::endl;
}

void GameState::generate()
{
	std::cout << "asd";

	m_player = new Player(sf::Vector2f(256, 256));
	m_player->setVelocity(sf::Vector2f(0, 0));
	m_player->setTexture(*m_RM->getTexture("wizard"));
	m_objects.push_back(m_player);



	//generate starting platform
	for (unsigned j = 0; j < 16; j++)
	{
		addTile(Tile::TileType::normal, j - 15.0f, 4);
	}
	addTile(Tile::TileType::bouncer, 1, 4);
	addTile(Tile::TileType::bouncer, 2, 4);
	for (unsigned k = 0; k < 4; k++)
	{
		addTile(Tile::TileType::danger, k+3, 4);
	}
	addTile(Tile::TileType::bouncer, 8, 4);
	addTile(Tile::TileType::bouncer, 7, 4);
	//set seed
	srand(time(NULL));

	int levelHeight = 4; //height of the "possible" platform
	int gapWidth = 0;    //obstacle width [0...3]
	int heightLength = 0;//length of the platform that has been generated on the current height
	int totalLength = 0;
    int minPlat = 3;
	bool bouncerGap = false;
	//generate level
	float levelLength = 50 + 50 * kakkaa;

    if (kakkaa > 0)
    {
        minPlat = 1;
    }

	for (unsigned i = 10; i < levelLength+1; i++)
	{
        if (i % 50 == 0)
        {
            addTile((i == levelLength) ? Tile::TileType::objective : Tile::TileType::checkpoint, i, levelHeight-1);
            continue;
        }
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
			if (rand() % 4 == 0 && heightLength > minPlat)
			{
				//start a gap
				bouncerGap = false;
				gapWidth++;
				if (rand() % 4 == 0)
				{
					addTile(Tile::TileType::bouncer, i, levelHeight);
				}
			}
			else if ((rand() % 5 == 0 && heightLength > 1))
			{
				addTile(Tile::TileType::danger, i, levelHeight);
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
		if (totalLength == levelLength-11 && !objective)
		{			
			if (objective == false) {
				objective = true;
				std::cout << objective << std::endl;
				totalLength++;
				addTile(Tile::TileType::objective, i + 1, levelHeight - 1);
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
    //for (auto it : m_objects)
    //{
    //    if (it->getType() == TYPE::TILE)
    //    {
    //        Tile* tile = static_cast<Tile*>(it);
    //        if (tile->getTileType() == Tile::TileType::danger)
    //        {
				//tile->updateOrigin();
    //            tile->setRotation(tile->getRotation() + dt * 100);
    //        }
    //    }
    //}
	movePlayer(dt);
	if (m_player->getPosition().y <= 1390)
	{
		sprite.setPosition((m_player->getPosition().x / 1.25) - 1000, sprite.getPosition().y);
	}
	if (finished)
	{
		finish.play();
		levelFinish();
	}
}

void GameState::draw(sf::RenderWindow &window)
{
    sf::RectangleShape r;
    r.setFillColor(sf::Color(255, 255, 255));
    r.setSize(sf::Vector2f(2048.0f, 3072.0f));
    r.setPosition(window.getView().getCenter().x - 1024.0f, 1370.0f + 1024.0f);
    window.draw(r);
	window.draw(sprite);
	//sf::Mouse::getPosition(window);
	if (m_player->getPosition().y <= 4000)
	{
		sf::View playerView(m_player->getPosition(), (sf::Vector2f)window.getSize()*2.0f);
		window.setView(playerView);
	}
	

	for (auto it : m_objects)
	{
		it->draw(window);
	}
}

void GameState::movePlayer(float dt)
{
	sf::Vector2f prev = m_player->getPosition();
	m_player->getHSpeed() = 20;
	m_player->getVSpeed() = m_player->getVelocity().y;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_player->getHSpeed() += 800* dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_player->getHSpeed() -= 800 * dt;
	
	//check if can fall
	m_player->move(0, 1);
	if (!getPlayerCollision()) //fall or move back
	{
		m_player->getVSpeed() += 60* dt;
	}
	else
	{
		m_player->getVSpeed() = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump.play();
			m_player->getVSpeed() = -27.5f;
		}
	}
	m_player->move(0, -1);

	//try to move
	GameObject* other = nullptr;

	//x
	m_player->move(m_player->getHSpeed(), 0);
	other = getPlayerCollision();
	if (other)
	{
		//move next to the wall
		float dx = other->getPosition().x - m_player->getPosition().x; //gap between the player and the wall
		m_player->move(((dx > 0) ? ( - m_player->getBoundingBox().width ) : 128.0) + dx, 0);
		m_player->getHSpeed() = 0;
	}
	m_player->move(0, m_player->getVSpeed());
	other = getPlayerCollision();
	if (other)
	{
		//move next to the wall
		float dy = other->getPosition().y - m_player->getPosition().y; //gap between the player and the wall
		m_player->move(0, dy + ((dy > 0) ? -m_player->getBoundingBox().height : 128.0f));
		m_player->getVSpeed() = 0;
	}

	m_player->setVelocity(sf::Vector2f(m_player->getHSpeed(), m_player->getVSpeed()));

	if (m_player->getPosition().y > 8000)
	{
		//m_player->destroy();
		std::cout << "haha kuolit!";
		fall.play();
		sf::Vector2f pos = m_player->getPosition();
		m_player->move(-pos.x + 256, -pos.y+400);
        m_player->move(m_checkpoint.x - 256, m_checkpoint.y - 400);
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
				Tile::TileType tileType = dynamic_cast<Tile*>(it)->getTileType();
				switch (tileType)
				{
					case Tile::normal: {
						//Do nothing
						break;
					}
					case Tile::danger: {
						fall.play();
						sf::Vector2f pos = m_player->getPosition();
						m_player->move(-pos.x + 256, -pos.y+400);
                        m_player->move(m_checkpoint.x - 256, m_checkpoint.y - 400);
						m_player->setVelocity(sf::Vector2f());
						return nullptr;
						break;
					}
					case Tile::bouncer: {
						jump.play();
						m_player->getVSpeed() = -35.0f;
						return nullptr;
						break;
					}
					case Tile::objective: {
						std::cout << "Level finished\n";
						finished = true;
						break;
					}
                    case Tile::checkpoint: {
                        std::cout << "CP!\n";
						checkpoint.play();
                        m_checkpoint = it->getPosition() - sf::Vector2f(32.0f, 128.0f);
                        dynamic_cast<Tile*>(it)->setTileType(Tile::TileType::normal);
                        break;
                    }
					default: {
						//Something happened
						break;
					}
				}
				return it;
			}
		}

	}
	return nullptr;
}
void GameState::levelFinish()
{
    switch (m_level)
    {
    case 0: m_manager->levelComplete(LEVEL_0_COMPLETED); break;
    case 1: m_manager->levelComplete(LEVEL_1_COMPLETED); break;
    case 2: m_manager->levelComplete(LEVEL_2_COMPLETED); break;
    default: break;
    }
	m_manager->setState(new MenuState(m_manager));
}

#endif
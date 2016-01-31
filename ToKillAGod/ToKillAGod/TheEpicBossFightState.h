#ifndef BOSS_FIGHT_STATE_H
#define BOSS_FIGHT_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"
#include "Player.h"
#include "ÜberEpicBoss.hpp"
#include "Projectile.hpp"
#include "ParticleManager.h"
#include <SFML\Audio.hpp>
class StateManager;

class BossFightScene
    :public State
{
public:
    BossFightScene(StateManager* manager);
    ~BossFightScene();
    void draw(sf::RenderWindow &window)override;
    void update(const float dt)override;
	GameObject* getPlayerCollisions();
private:
    void loadResources();
    void generate();
    void movePlayers(float dt);
    void circleCollisions();
    ResourceManager* m_RM;
    ParticleManager* m_PM;
    bool objective = false;
    bool finished = false;
	float bossShootTimer;
	float projectileLifeTime;
    Player* m_player_0;
    Player* m_player_1;
    Player* m_player_2;

	sf::SoundBuffer shootbuffer;
	sf::SoundBuffer ExplosionBuffer;
	sf::SoundBuffer stepOnTriangleBuffer;
	sf::SoundBuffer fallbuffer;

	sf::Sound shootSound;
	sf::Sound explosionSound;
	sf::Sound stepOnTriangleSound;
	sf::Sound fallSound;
	sf::Music bossMusic;

    sf::Sprite m_circle_0;
    sf::Sprite m_circle_1;
    sf::Sprite m_circle_2;

    sf::Sprite m_circle_effect_0;
    sf::Sprite m_circle_effect_1;
    sf::Sprite m_circle_effect_2;

    bool player_0_at_destination = false;
    bool player_1_at_destination = false;
    bool player_2_at_destination = false;

    bool m_bossfight = false;
    float m_spawnTimer = 0;
    float m_end = 0;

    sf::View m_gameView;

    ÜberEpicBoss* m_boss;

	float m_hpYPosition = 550.0f;
    
};


BossFightScene::BossFightScene(StateManager* manager)
    :State(manager)
{
    //create players
    m_player_0 = new Player(sf::Vector2f(-32.0f, -600.0f));
    m_player_1 = new Player(sf::Vector2f(-32.0f, -600.0f));
    m_player_2 = new Player(sf::Vector2f(-32.0f, -600.0f));

    m_objects.push_back(m_player_0);
    m_objects.push_back(m_player_1);
    m_objects.push_back(m_player_2);

	m_player_2->initHP(sf::Vector3f(255.0, 255.0, 255.0), 250.0f);
	m_player_1->initHP(sf::Vector3f(136.0, 0.0, 21.0), 250.0f);
	m_player_0->initHP(sf::Vector3f(0.0, 255.0, 255.0), 250.0f);

	m_player_0->setHPPosition(sf::Vector2f(300, m_hpYPosition));
	m_player_1->setHPPosition(sf::Vector2f(0, m_hpYPosition));
	m_player_2->setHPPosition(sf::Vector2f(-300, m_hpYPosition));

    loadResources();
	shootbuffer.loadFromFile("audio/bossShoot.wav");
	ExplosionBuffer.loadFromFile("audio/bossExplosion.wav");
	stepOnTriangleBuffer.loadFromFile("audio/stepontriangle.wav");
	fallbuffer.loadFromFile("audio/falldown.wav");
	bossMusic.openFromFile("audio/bossMusic.wav");
	shootSound.setBuffer(shootbuffer);
	explosionSound.setBuffer(ExplosionBuffer);
	stepOnTriangleSound.setBuffer(stepOnTriangleBuffer);
	fallSound.setBuffer(fallbuffer);
    generate();
}

BossFightScene::~BossFightScene()
{
    for (auto it : m_objects)
    {
        delete it;
    }
}

void BossFightScene::movePlayers(float dt)
{
    float move_speed = 200.0f;

    if (!player_0_at_destination || m_boss)
    {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	&& (!m_bossfight || m_player_0->getPosition().x >= -512))
			m_player_0->move(-dt * move_speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (!m_bossfight || m_player_0->getPosition().x <= 448))
            m_player_0->move(dt * move_speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)	&& (!m_bossfight || m_player_0->getPosition().y >= -768))
            m_player_0->move(0, -dt * move_speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)	&& (!m_bossfight || m_player_0->getPosition().y <= 192))
            m_player_0->move(0, dt * move_speed);
    }
    if (!player_2_at_destination || m_boss)
    {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (!m_bossfight || m_player_2->getPosition().x >= -512))
			m_player_2->move(-dt * move_speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (!m_bossfight || m_player_2->getPosition().x <= 448))
			m_player_2->move(dt * move_speed, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (!m_bossfight || m_player_2->getPosition().y >= -768))
			m_player_2->move(0, -dt * move_speed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (!m_bossfight || m_player_2->getPosition().y <= 192))
            m_player_2->move(0, dt * move_speed);
    }
    if (!player_1_at_destination || m_boss)
    {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && (!m_bossfight || m_player_1->getPosition().x >= -512))
			m_player_1->move(-dt * move_speed, 0);									 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && (!m_bossfight || m_player_1->getPosition().x <= 448))
			m_player_1->move(dt * move_speed, 0);									 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && (!m_bossfight || m_player_1->getPosition().y >= -768))
			m_player_1->move(0, -dt * move_speed);									 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && (!m_bossfight || m_player_1->getPosition().y <= 192))
            m_player_1->move(0, dt * move_speed);
    }
}

GameObject* BossFightScene::getPlayerCollisions()
{
	for (GameObject* it : m_projectiles)
	{
		GameObject* temp = m_player_0->circleCollision(it);
		if (temp != nullptr && !m_player_0->isDestroyed()) {
			fallSound.play();
			m_player_0->hit(1.25f);
			temp->destroy();
		}
		temp = m_player_1->circleCollision(it);
		if (temp != nullptr&& !m_player_1->isDestroyed()) {
			fallSound.play();
			m_player_1->hit(1.25f);
			temp->destroy();
		}
		temp = m_player_2->circleCollision(it);
		if (temp != nullptr&& !m_player_2->isDestroyed()) {
			fallSound.play();
			m_player_2->hit(1.25f);
			temp->destroy();
		}
	}

	return nullptr;
}
void BossFightScene::update(float dt)
{

	srand(time(NULL));

	if (m_player_0->hp() <= 0)
	{
        m_player_0->destroy();
	}
	if (m_player_1->hp() <= 0)
	{
        m_player_1->destroy();
	}
	if (m_player_2->hp() <= 0)
	{
        m_player_2->destroy();
	}

	//if (projectileLifeTime >= 7 && m_projectiles.size() > 0)
	//{
	//	m_projectiles.erase(m_projectiles.begin(),m_projectiles.end());
	//	projectileLifeTime = 0;
	//}
	//else if (m_projectiles.size() > 0){ projectileLifeTime += dt; }
    for (auto it : m_objects)
    {
        it->update(dt);
    }
	for (auto it : m_projectiles)
	{
		it->update(dt);
	}
	if (m_bossfight&&m_boss->hp() <= 0)
	{
		//cue the explosions!!!!!1111!!!
		explosionSound.play();
        for (int i = 0; i < 500; i++)
        {
            m_PM->createParticle(m_RM->getTexture("star"),
                m_boss->getPosition().x, m_boss->getPosition().y,
                1500.0f,
                0.0f,
                5.0f, 
                1500.0f, 360.0f, 4.9f);
        }
        m_bossfight = false;
        m_end = 10.0f;
        m_boss->destroy();
	}
    movePlayers(dt);
    if (m_spawnTimer > 0)
    {
        //perform ritual
        m_spawnTimer -= dt*5;
        float scale = sin(m_spawnTimer) + 1.0f;
        m_circle_effect_0.setScale(scale, scale);
        m_circle_effect_1.setScale(scale, scale);
        m_circle_effect_2.setScale(scale, scale);
    }
    if (m_end > 0)
    {
        m_end -= dt;
        if (m_end < 0)
        {
            m_RM->clearAll();
            m_PM->clearAll();
            m_manager->levelComplete(LevelFlag::GAME_COMPLETED);
            m_manager->setState(new MenuState(m_manager));
            return;
        }
    }

    //collisions:
    if (!m_bossfight && m_end == 0.0f)
    {
        circleCollisions();
        if (player_0_at_destination && player_1_at_destination && player_2_at_destination)
        {
            m_bossfight = true;
			bossMusic.setLoop(true);
			bossMusic.play();
            m_boss = new ÜberEpicBoss(0.0f, -512.f);
            m_objects.push_back(m_boss);
            m_spawnTimer = 3.1415926535f;

            //TODO: add more cool effects when the big bad boss is summoned
			shootSound.play();
            for (int i = 0; i < 50; i++)
            {
				m_projectiles.push_back(new Projectile(0.0f, -700.0f, 0.0f, 0.0f));
            }
        }
    }
    else
    {
		BossFightScene::getPlayerCollisions();

		if (m_hpYPosition > 230) {
			m_hpYPosition = m_player_0->getHPPos().y - 1.5f;
			m_player_0->setHPPosition(sf::Vector2f(300, m_hpYPosition));
			m_player_1->setHPPosition(sf::Vector2f(0,	 m_hpYPosition));
			m_player_2->setHPPosition(sf::Vector2f(-300,  m_hpYPosition));
		}

        //move shields to players
        if (m_player_0->hp() > 0) m_circle_effect_0.setPosition(m_player_0->getPosition() + sf::Vector2f(32.0f, 32.0f));
        if (m_player_1->hp() > 0) m_circle_effect_1.setPosition(m_player_1->getPosition() + sf::Vector2f(32.0f, 32.0f));
        if (m_player_2->hp() > 0) m_circle_effect_2.setPosition(m_player_2->getPosition() + sf::Vector2f(32.0f, 32.0f));

        if (m_end == 0.0f)
        {
            //shoot particles to boss
			if (m_player_0->hp() > 0) m_PM->createParticle(m_RM->getTexture("spark"),
                m_player_0->getPosition().x, m_player_0->getPosition().y,
                500.0f,
                atan2f(
                m_boss->getPosition().y - m_player_0->getPosition().y,
                m_boss->getPosition().x - m_player_0->getPosition().x),
                1.5f, 180.0f, 0.1f, 0.5f);
			if (m_player_1->hp() > 0) m_PM->createParticle(m_RM->getTexture("spark_red"),
                m_player_1->getPosition().x, m_player_1->getPosition().y,
                500.0f,
                atan2f(
                m_boss->getPosition().y - m_player_1->getPosition().y,
                m_boss->getPosition().x - m_player_1->getPosition().x),
                1.5f, 180.0f, 0.1f, 0.5f);
			if (m_player_2->hp() > 0) m_PM->createParticle(m_RM->getTexture("spark_white"),
                m_player_2->getPosition().x, m_player_2->getPosition().y,
                500.0f,
                atan2f(
                m_boss->getPosition().y - m_player_2->getPosition().y,
                m_boss->getPosition().x - m_player_2->getPosition().x),
                1.5f, 180.0f, 0.1f, 0.5f);
        
			if (bossShootTimer >= 2.0f && (!m_player_0->isDestroyed() || !m_player_1->isDestroyed() || !m_player_2->isDestroyed())) {

				//Get random player
				GameObject* target = m_objects[rand() % 3];
				while (target->isDestroyed() && target->getType() != TYPE::PLAYER) {
					target = m_objects[rand() % 3];
				}
				
				shootSound.play();

				switch (rand() % 3)
				{
				case 0:
					for (int i = 0; i < 5; i++)
					{
						m_projectiles.push_back(new Projectile(m_boss->getPosition().x, m_boss->getPosition().y, target->getPosition().x, target->getPosition().y, -atan2f(target->getPosition().y - m_boss->getPosition().y, target->getPosition().x - m_boss->getPosition().x)));
					}
					break;
				case 1:
					for (int i = 0; i < 5; i++)
					{
						m_projectiles.push_back(new Projectile(m_boss->getPosition().x, m_boss->getPosition().y, target->getPosition().x, target->getPosition().y, -atan2f(target->getPosition().y - m_boss->getPosition().y, target->getPosition().x - m_boss->getPosition().x)*i / 3.14f));
					}
					break;
				default:
					for (int i = 0; i < 15; i++)
					{
						m_projectiles.push_back(new Projectile(m_boss->getPosition().x, m_boss->getPosition().y, 0.0f, 0.0f));
					}
					break;
				}
				bossShootTimer = 0;
			}
			else {
				bossShootTimer += dt;
			}
        }

        //stuff
        m_PM->update(dt);

        //delete deleted objects
        for (unsigned i = 0; i < m_objects.size(); i++)
        {
            if (m_objects[i]->isDestroyed())
            {
				if (m_objects[i] != m_player_0 && m_objects[i] != m_player_1 && m_objects[i] != m_player_2) {
					delete m_objects[i];
					m_objects.erase(m_objects.begin() + i);
					i--;
				}
            }
        }
		for (unsigned i = 0; i < m_projectiles.size(); i++)
		{
			if (m_projectiles[i]->isDestroyed())
			{
				delete m_projectiles[i];
				m_projectiles.erase(m_projectiles.begin() + i);
				i--;
			}
		}
    }

    //rotate shields
    m_circle_effect_0.rotate(dt * 120);
    m_circle_effect_1.rotate(dt * 120);
    m_circle_effect_2.rotate(dt * 120);

	if (m_player_0->isDestroyed() && m_player_1->isDestroyed() && m_player_2->isDestroyed()) {
		m_RM->clearAll();
		m_PM->clearAll();
		m_manager->setState(new MenuState(m_manager));
		return;
	}
}

void BossFightScene::circleCollisions()
{
    float dx0 = (m_player_0->getPosition().x + 32.0f) - (m_circle_0.getPosition().x);
    float dy0 = (m_player_0->getPosition().y + 32.0f) - (m_circle_0.getPosition().y);
                                                                                   
    float dx1 = (m_player_1->getPosition().x + 32.0f) - (m_circle_1.getPosition().x);
    float dy1 = (m_player_1->getPosition().y + 32.0f) - (m_circle_1.getPosition().y);
                                                                                   
    float dx2 = (m_player_2->getPosition().x + 32.0f) - (m_circle_2.getPosition().x);
    float dy2 = (m_player_2->getPosition().y + 32.0f) - (m_circle_2.getPosition().y);

    float range = 32.0f;

    if (!player_0_at_destination)
        if (dx0*dx0 + dy0*dy0 < range*range)
        {
			stepOnTriangleSound.play();
            player_0_at_destination = true;
            m_circle_effect_0.setPosition(m_player_0->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
    if (!player_1_at_destination)
        if (dx1*dx1 + dy1*dy1 < range*range)
        {
			stepOnTriangleSound.play();
            player_1_at_destination = true;
            m_circle_effect_1.setPosition(m_player_1->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
    if (!player_2_at_destination)
        if (dx2*dx2 + dy2*dy2 < range*range)
        {
			stepOnTriangleSound.play();
            player_2_at_destination = true;
            m_circle_effect_2.setPosition(m_player_2->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
}

void BossFightScene::loadResources()
{
    //get texture manager
    m_RM = ResourceManager::getInstance();
    m_PM = ParticleManager::getInstance();

    m_RM->loadTexture("textures/BigBadBoss.png", "BigBadBoss");
    m_RM->loadTexture("textures/projectile.png", "Projectile1");
    m_RM->loadTexture("textures/spark.png", "spark");
	m_RM->loadTexture("textures/spark_white.png", "spark_white");
	m_RM->loadTexture("textures/spark_red.png", "spark_red");
    m_RM->loadTexture("textures/tile_objective.png", "star");

    m_player_0->setTexture(*m_RM->loadTexture("textures/Player_blue.png", "player0"));
    m_player_1->setTexture(*m_RM->loadTexture("textures/Player_red.png", "player1"));
    m_player_2->setTexture(*m_RM->loadTexture("textures/Player_white.png", "player2"));

    //load destination sprites & their effects
    m_circle_2.setTexture(*m_RM->loadTexture("textures/finalTile_1.png", "circle2"));
    m_circle_0.setTexture(*m_RM->loadTexture("textures/finalTile_3.png", "circle0"));
    m_circle_1.setTexture(*m_RM->loadTexture("textures/finalTile_2.png", "circle1"));

    m_circle_0.setOrigin(111.0f, 61.5f);
    m_circle_1.setOrigin(116.5f, 51.0f);
    m_circle_2.setOrigin(113.5f, 62.5f);

    m_circle_effect_0.setTexture(*m_RM->loadTexture("textures/shield_blue.png", "effect0"));
    m_circle_effect_1.setTexture(*m_RM->loadTexture("textures/shield_red.png", "effect1"));
    m_circle_effect_2.setTexture(*m_RM->loadTexture("textures/shield_white.png", "effect2"));

    m_circle_effect_0.setPosition(-9001, -9001);
    m_circle_effect_1.setPosition(-9001, -9001);
    m_circle_effect_2.setPosition(-9001, -9001);

    m_circle_effect_0.setOrigin(128.0f, 128.0f);
    m_circle_effect_1.setOrigin(128.0f, 128.0f);
    m_circle_effect_2.setOrigin(128.0f, 128.0f);
}

void BossFightScene::generate()
{
    //set player positions
    m_player_0->move(256.0f, 1024.0f);
    m_player_1->move(0.0f, 1024.0f);
    m_player_2->move(-256.0f, 1024.0f);

    m_circle_0.setPosition(256.0f, 0.0f);
    m_circle_1.setPosition(0.0f, 64.0f);
    m_circle_2.setPosition(-256.0f, 0.0f);
}

void BossFightScene::draw(sf::RenderWindow& window)
{
    m_PM->draw(window);
	if (!m_bossfight && m_end == 0.0f) {
		sf::Vector2f aveRage = (m_player_0->getPosition() + m_player_1->getPosition() + m_player_2->getPosition()) / 3.0f;
		m_gameView.setCenter(aveRage);
		window.setView(m_gameView);
	}
	else if (m_gameView.getCenter().y  >= -260) { //Vois parantaa, mutten jaksa
		m_gameView.setCenter(0.0f, m_gameView.getCenter().y -1.5f);
		window.setView(m_gameView);
	}

	window.draw(m_circle_0);
	window.draw(m_circle_1);
	window.draw(m_circle_2);

	if (m_player_0->hp() > 0) window.draw(m_circle_effect_0);
	if (m_player_1->hp() > 0) window.draw(m_circle_effect_1);
	if (m_player_2->hp() > 0) window.draw(m_circle_effect_2);

    for (auto it : m_objects)
    {
		if (!it->isDestroyed())
	        it->draw(window);
    }
	for (auto it : m_projectiles)
	{
		it->draw(window);
	}

	if (m_bossfight) {
		if(m_player_0->hp() > 0) m_player_0->drawHP(window);
		if(m_player_1->hp() > 0) m_player_1->drawHP(window);
		if(m_player_2->hp() > 0) m_player_2->drawHP(window);
	}
}

#endif
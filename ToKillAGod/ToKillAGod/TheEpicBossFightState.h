#ifndef BOSS_FIGHT_STATE_H
#define BOSS_FIGHT_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"
#include "Player.h"
#include "ÜberEpicBoss.hpp"

class StateManager;

class BossFightScene
    :public State
{
public:
    BossFightScene(StateManager* manager);
    ~BossFightScene();
    void draw(sf::RenderWindow &window)override;
    void update(const float dt)override;
private:
    void loadResources();
    void generate();
    void movePlayers(float dt);
    void circleCollisions();
    ResourceManager* m_RM;
    bool objective = false;
    bool finished = false;

    Player* m_player_0;
    Player* m_player_1;
    Player* m_player_2;

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

    sf::View m_gameView;

    ÜberEpicBoss* m_boss;
};


BossFightScene::BossFightScene(StateManager* manager)
    :State(manager)
{
    //create players
    m_player_0 = new Player(sf::Vector2f(0.0f, 0.0f));
    m_player_1 = new Player(sf::Vector2f(0.0f, 0.0f));
    m_player_2 = new Player(sf::Vector2f(0.0f, 0.0f));

    m_objects.push_back(m_player_0);
    m_objects.push_back(m_player_1);
    m_objects.push_back(m_player_2);

    loadResources();

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m_player_0->move(-dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m_player_0->move(dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            m_player_0->move(0, -dt * move_speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            m_player_0->move(0, dt * move_speed);
    }
    if (!player_2_at_destination || m_boss)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_player_2->move(-dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_player_2->move(dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_player_2->move(0, -dt * move_speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            m_player_2->move(0, dt * move_speed);
    }
    if (!player_1_at_destination || m_boss)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            m_player_1->move(-dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            m_player_1->move(dt * move_speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            m_player_1->move(0, -dt * move_speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            m_player_1->move(0, dt * move_speed);
    }
}

void BossFightScene::update(float dt)
{
    for (auto it : m_objects)
    {
        it->update(dt);
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
    //collisions:
    if (!m_bossfight)
    {
        circleCollisions();
        if (player_0_at_destination && player_1_at_destination && player_2_at_destination)
        {
            m_bossfight = true;
            m_boss = new ÜberEpicBoss(0.0f, -512.f);
            m_objects.push_back(m_boss);
            m_spawnTimer = 3.1415926535f;
            std::cout << "BOSSFOO!\n";
        }
    }
    else
    {
        //move shields to players
        m_circle_effect_0.setPosition(m_player_0->getPosition() + sf::Vector2f(32.0f, 32.0f));
        m_circle_effect_1.setPosition(m_player_1->getPosition() + sf::Vector2f(32.0f, 32.0f));
        m_circle_effect_2.setPosition(m_player_2->getPosition() + sf::Vector2f(32.0f, 32.0f));

        //projectile collisions & stuff
    }

    //rotate shields
    m_circle_effect_0.rotate(dt * 120);
    m_circle_effect_1.rotate(dt * 120);
    m_circle_effect_2.rotate(dt * 120);
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
            player_0_at_destination = true;
            m_circle_effect_0.setPosition(m_player_0->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
    if (!player_1_at_destination)
        if (dx1*dx1 + dy1*dy1 < range*range)
        {
            player_1_at_destination = true;
            m_circle_effect_1.setPosition(m_player_1->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
    if (!player_2_at_destination)
        if (dx2*dx2 + dy2*dy2 < range*range)
        {
            player_2_at_destination = true;
            m_circle_effect_2.setPosition(m_player_2->getPosition() + sf::Vector2f(32.0f, 32.0f));
        }
}

void BossFightScene::loadResources()
{
    //get texture manager
    m_RM = ResourceManager::getInstance();

    m_RM->loadTexture("textures/BigBadBoss.png", "BigBadBoss");
    m_RM->loadTexture("textures/projectile.png", "Projectile1");

    m_player_0->setTexture(*m_RM->loadTexture("textures/Player_blue.png", "player0"));
    m_player_1->setTexture(*m_RM->loadTexture("textures/Player_red.png", "player1"));
    m_player_2->setTexture(*m_RM->loadTexture("textures/Player_white.png", "player2"));

    //load destination sprites & their effects
    m_circle_0.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle0"));
    m_circle_1.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle1"));
    m_circle_2.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle2"));

    m_circle_0.setOrigin(64.0f, 64.0f);
    m_circle_1.setOrigin(64.0f, 64.0f);
    m_circle_2.setOrigin(64.0f, 64.0f);

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
    sf::Vector2f aveRage = (m_player_0->getPosition() + m_player_1->getPosition() + m_player_2->getPosition()) / 3.0f;
    m_gameView.setCenter(aveRage);
    window.setView(m_gameView);

    window.draw(m_circle_0);
    window.draw(m_circle_1);
    window.draw(m_circle_2);

    window.draw(m_circle_effect_0);
    window.draw(m_circle_effect_1);
    window.draw(m_circle_effect_2);

    for (auto it : m_objects)
    {
        it->draw(window);
    }
}

#endif
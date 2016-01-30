#ifndef BOSS_FIGHT_STATE_H
#define BOSS_FIGHT_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "Button.hpp"
#include "Tile.h"
#include "Player.h"

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

    bool m_boss = false;
};


BossFightScene::BossFightScene(StateManager* manager)
    :State(manager)
{
    //create players
    m_player_0 = new Player(sf::Vector2f(0.0f, 256.0f));
    m_player_1 = new Player(sf::Vector2f(128.0f, 256.0f));
    m_player_2 = new Player(sf::Vector2f(256.0f, 256.0f));

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
    if (!player_0_at_destination || m_boss)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m_player_1->move(-dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m_player_1->move(dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            m_player_1->move(0, -dt * 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            m_player_1->move(0, dt * 10);
    }
    if (!player_1_at_destination || m_boss)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_player_1->move(-dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_player_1->move(dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            m_player_1->move(0, -dt * 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            m_player_1->move(0, dt * 10);
    }
    if (!player_2_at_destination || m_boss)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
            m_player_1->move(-dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
            m_player_1->move(dt * 10, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
            m_player_1->move(0, -dt * 10);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
            m_player_1->move(0, dt * 10);
    }
}

void BossFightScene::update(float dt)
{
    movePlayers(dt);
    //collisions:
    if (!m_boss)
    {
        circleCollisions();
        if (player_0_at_destination && player_1_at_destination && player_2_at_destination)
        {
            m_boss = true;
        }
    }
    else
    {

    }
}

void BossFightScene::circleCollisions()
{
    float dx0 = m_player_0->getPosition().x - m_circle_0.getPosition().x;
    float dy0 = m_player_0->getPosition().y - m_circle_0.getPosition().y;

    float dx1 = m_player_1->getPosition().x - m_circle_1.getPosition().x;
    float dy1 = m_player_1->getPosition().y - m_circle_1.getPosition().y;

    float dx2 = m_player_2->getPosition().x - m_circle_2.getPosition().x;
    float dy2 = m_player_2->getPosition().y - m_circle_2.getPosition().y;

    float range = 32.0f;

    if (!player_0_at_destination)
        if (dx0*dx0 + dy0*dy0 < range*range)
        {
            player_0_at_destination = true;
            m_circle_effect_0.setPosition(m_player_0->getPosition());
        }
    if (!player_1_at_destination)
        if (dx1*dx1 + dy1*dy1 < range*range)
        {
            player_1_at_destination = true;
            m_circle_effect_0.setPosition(m_player_0->getPosition());
        }
    if (!player_2_at_destination)
        if (dx2*dx2 + dy2*dy2 < range*range)
        {
            player_2_at_destination = true;
            m_circle_effect_0.setPosition(m_player_0->getPosition());
        }
}

void BossFightScene::loadResources()
{
    //get texture manager
    m_RM = ResourceManager::getInstance();

    m_player_0->setTexture(*m_RM->loadTexture("textures/Player_blue.png", "player0"));
    m_player_1->setTexture(*m_RM->loadTexture("textures/Player_red.png", "player1"));
    m_player_2->setTexture(*m_RM->loadTexture("textures/Player_white.png", "player2"));

    m_objects.push_back(m_player_0);
    m_objects.push_back(m_player_1);
    m_objects.push_back(m_player_2);

    //load destination sprites & their effects
    m_circle_0.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle0"));
    m_circle_1.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle1"));
    m_circle_2.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "circle2"));

    m_circle_effect_0.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "effect0"));
    m_circle_effect_1.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "effect0"));
    m_circle_effect_2.setTexture(*m_RM->loadTexture("textures/exitBtn_pressed.png", "effect0"));

    m_circle_effect_0.setPosition(-9001, -9001);
    m_circle_effect_1.setPosition(-9001, -9001);
    m_circle_effect_2.setPosition(-9001, -9001);
}

void BossFightScene::generate()
{
    m_circle_0.setPosition(0.0f, 128.0f);
    m_circle_0.setPosition(128.0f, 128.0f);
    m_circle_0.setPosition(256.0f, 128.0f);
}

#endif
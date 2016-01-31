#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "State.hpp"
#include "ResourceManager.h"
#include "ParticleManager.h"
#include "Button.hpp"

class StateManager;

class MenuState
	:public State
{
public:
	MenuState(StateManager* manager);
	~MenuState();
	void draw(sf::RenderWindow &window)override;
    void update(const float dt)override;
private:
	float m_totalTime = 0;

	ResourceManager* m_RM;
    ParticleManager* m_PM;

	CircleButton* level0;
	CircleButton* level1;
	CircleButton* level2;
    CircleButton* center;

    sf::Sprite* wizard0;
    sf::Sprite* wizard1;
    sf::Sprite* wizard2;
};

MenuState::MenuState(StateManager* manager)
	:State(manager)
{
	m_RM = ResourceManager::getInstance();
    m_PM = ParticleManager::getInstance();

	m_RM->loadTexture("textures/Level0.png", "level0");
	m_RM->loadTexture("textures/Level0_pressed.png", "level0_p");
    m_RM->loadTexture("textures/Level0_complete.png", "level0_c");
	m_RM->loadTexture("textures/Level1.png", "level1");
	m_RM->loadTexture("textures/Level1_pressed.png", "level1_p");
    m_RM->loadTexture("textures/Level1_complete.png", "level1_c");
    m_RM->loadTexture("textures/Level2.png", "level2");
    m_RM->loadTexture("textures/Level2_pressed.png", "level2_p");
    m_RM->loadTexture("textures/Level2_complete.png", "level2_c");

    m_RM->loadTexture("textures/Player_blue.png", "wizard_0");
    m_RM->loadTexture("textures/Player_red.png", "wizard_1");
    m_RM->loadTexture("textures/Player_white.png", "wizard_2");

    m_RM->loadTexture("textures/levelFinal.png", "center");
    m_RM->loadTexture("textures/levelFinal_pressed.png", "center_p");

    m_RM->loadTexture("textures/spark.png", "spark0");
    m_RM->loadTexture("textures/spark_red.png", "spark1");
    m_RM->loadTexture("textures/spark_white.png", "spark2");

	level0 = new CircleButton(0, 0, 128);
	level0->setTexture(*m_RM->getTexture("level0"));
	m_objects.push_back(level0);

	level1 = new CircleButton(0, 0, 128);
	level1->setTexture(*m_RM->getTexture("level1"));
	m_objects.push_back(level1);

	level2 = new CircleButton(0, 0, 128);
	level2->setTexture(*m_RM->getTexture("level2"));
	m_objects.push_back(level2);

    center = new CircleButton(512 - 128, 512 - 128 , 128);
    center->setTexture(*m_RM->getTexture("center"));
    m_objects.push_back(center);

    wizard0 = new sf::Sprite(*m_RM->getTexture("wizard_0"));
    wizard1 = new sf::Sprite(*m_RM->getTexture("wizard_1"));
    wizard2 = new sf::Sprite(*m_RM->getTexture("wizard_2"));

    wizard0->setScale(4, 4);
    wizard1->setScale(4, 4);
    wizard2->setScale(4, 4);
}

#include "GameState.h"
#include "TheEpicBossFightState.h"

MenuState::~MenuState()
{
	delete level0;
	delete level1;
	delete level2;

    delete wizard0;
    delete wizard1;
    delete wizard2;

    delete center;
    m_RM->deleteTexture("level0");
    m_RM->deleteTexture("level0_p");
    m_RM->deleteTexture("level0_c");
    m_RM->deleteTexture("level1");
    m_RM->deleteTexture("level1_p");
    m_RM->deleteTexture("level1_c");
    m_RM->deleteTexture("level2");
    m_RM->deleteTexture("level2_p");
    m_RM->deleteTexture("level2_c");

    m_RM->deleteTexture("wizard_0");
    m_RM->deleteTexture("wizard_1");
    m_RM->deleteTexture("wizard_2");

    m_RM->deleteTexture("center");
    m_RM->deleteTexture("center_p");

    m_PM->clearAll();
}

void MenuState::update(const float dt)
{
	m_totalTime += dt;
	float pi = 3.1415926535f;
    float range = 128.0f + 128.0f * sqrt(2.0f);
	float centerX = 512 - 128;//= 320 - 128;
	float centerY = 512 - 128;//= 240 - 128;

    sf::Vector2f pos0 = sf::Vector2f((cos(m_totalTime + 4 * pi / 3)) * range + centerX, (sin(m_totalTime + 4 * pi / 3)) * range + centerY);
    sf::Vector2f pos1 = sf::Vector2f((cos(m_totalTime + 2 * pi / 3)) * range + centerX, (sin(m_totalTime + 2 * pi / 3)) * range + centerY);
    sf::Vector2f pos2 = sf::Vector2f((cos(m_totalTime + 0 * pi / 3)) * range + centerX, (sin(m_totalTime + 0 * pi / 3)) * range + centerY);

	level2->setPosition(pos0);
    level1->setPosition(pos1);
	level0->setPosition(pos2);

    if (m_manager->isLevelCompleted(0))
        m_PM->createParticle(m_RM->getTexture("spark0"), pos0.x + 128.0f, pos0.y + 128.0f, 800.0f, m_totalTime + 4 * pi / 3 + pi, 0.9f, 100.0f, 0.1f, 0.0f);
    if (m_manager->isLevelCompleted(1))
        m_PM->createParticle(m_RM->getTexture("spark1"), pos1.x + 128.0f, pos1.y + 128.0f, 800.0f, m_totalTime + 2 * pi / 3 + pi, 0.9f, 100.0f, 0.1f, 0.0f);
    if (m_manager->isLevelCompleted(2))
        m_PM->createParticle(m_RM->getTexture("spark2"), pos2.x + 128.0f, pos2.y + 128.0f, 800.0f, m_totalTime + 0 * pi / 3 + pi, 0.9f, 100.0f, 0.1f, 0.0f);

	for (auto it : m_objects)
	{
		if (it == level0)
		{
            if (!m_manager->isLevelCompleted(0))
            {
                if (level0->isHovering())
                {
                    level0->setTexture(*m_RM->getTexture("level0_p"));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        m_manager->setState(new GameState(m_manager, 0));
                        return;
                    }
                }
                else
                {
                    level0->setTexture(*m_RM->getTexture("level0"));
                }
            }
            else
            {
                level0->setTexture(*m_RM->getTexture("level0_c"));
            }
		}
		else if (it == level1)
		{
            if (!m_manager->isLevelCompleted(1))
            {
                if (level1->isHovering())
                {
                    level1->setTexture(*m_RM->getTexture("level1_p"));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        m_manager->setState(new GameState(m_manager, 1));
                        return;
                    }
                }
                else
                {
                    level1->setTexture(*m_RM->getTexture("level1"));
                }
            }
            else
            {
                level1->setTexture(*m_RM->getTexture("level1_c"));
            }
		}
		else if (it == level2)
		{
            if (!m_manager->isLevelCompleted(2))
            {
                if (level2->isHovering())
                {
                    level2->setTexture(*m_RM->getTexture("level2_p"));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        m_manager->setState(new GameState(m_manager, 2));
                        return;
                    }
                }
                else
                {
                    level2->setTexture(*m_RM->getTexture("level2"));
                }
            }
            else
            {
                level2->setTexture(*m_RM->getTexture("level2_c"));
            }
		}
        else if (it == center)
        {
            if (m_manager->isLevelCompleted(0) && m_manager->isLevelCompleted(1) && m_manager->isLevelCompleted(2))
            {
                if (center->isHovering())
                {
                    center->setTexture(*m_RM->getTexture("center_p"));
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        m_manager->setState(new BossFightScene(m_manager));
                        return;
                    }
                }
                else
                {
                    center->setTexture(*m_RM->getTexture("center"));
                }
            }
            else
            {
                center->setTexture(*m_RM->getTexture("center"));
            }
        }
	}

    m_PM->update(dt);
}

void MenuState::draw(sf::RenderWindow &window)
{
	//sf::Mouse::getPosition(window);
    m_PM->draw(window);

	window.setView(window.getDefaultView());

    for (auto it : m_objects)
    {
        it->draw(window);
    }

    if (m_manager->isLevelCompleted(0))
    {
        wizard0->setPosition(level0->getPosition());
        window.draw(*wizard0);
    }
    if (m_manager->isLevelCompleted(1))
    {
        wizard1->setPosition(level1->getPosition());
        window.draw(*wizard1);
    }
    if (m_manager->isLevelCompleted(2))
    {
        wizard2->setPosition(level2->getPosition());
        window.draw(*wizard2);
    }
}

#endif
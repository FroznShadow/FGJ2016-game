#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics/Sprite.hpp>
#include "ResourceManager.h"

class Particle
    :public sf::Sprite
{
public:
    Particle(float timer, float direction, float speed)
        :m_time(timer),
        m_direction(direction),
        m_speed(speed),
        m_life(0)
    {}
    ~Particle(){}

    void update(float dt)
    {
        move(cos(m_direction) * m_speed * dt, sin(m_direction) * m_speed * dt);
        m_life += dt;
        if (m_life > m_time)
        {
            m_destroy = true;
        }
        rotate(1000.0f * dt);
    }
    bool m_destroy = false;
private:
    float m_time;
    float m_life;
    float m_direction;
    float m_speed;

};

#endif
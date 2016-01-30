#ifndef PARTICLE_MANAGER_H
#define PARTICLE_MANAGER_H

#include <vector>
#include "Particle.h"
#include <SFML/Graphics/RenderWindow.hpp>

class ParticleManager
{
public:
    static ParticleManager* getInstance()
    {
        static ParticleManager m_instance;
        return &m_instance;
    }
    void update(float dt)
    {
        for (int i = 0; i < m_particles.size(); i++)
        {
            m_particles[i]->update(dt);
        }
        for (int j = 0; j < m_particles.size(); j++)
        {
            if (m_particles[j]->m_destroy)
            {
                m_particles.erase(m_particles.begin() + j);
                j--;
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (auto p : m_particles)
        {
            window.draw(*p);
        }
    }

    void createParticle(sf::Texture* texture, float x, float y, float speed, float direction, float time, float d_speed, float d_dir, float d_time)
    {
        m_particles.push_back(new Particle(time + randF(d_time), direction + randF(d_dir), speed + randF(d_speed)));
        m_particles[m_particles.size() - 1]->setTexture(*texture);
        m_particles[m_particles.size() - 1]->setPosition(x, y);
    }

    void clearAll()
    {
        m_particles.clear();
    }

private:
    float randF(float range)
    {
        return ((float)(rand() % 1000)) / 2000 * range - range;
    }
    ParticleManager(){}
    ~ParticleManager(){}
    static ParticleManager* m_instance;

    std::vector<Particle*> m_particles;
};

#endif
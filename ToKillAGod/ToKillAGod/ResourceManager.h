#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <iostream>

class ResourceManager
{
public:
	static ResourceManager* getInstance()
	{
		static ResourceManager m_instance;
		return &m_instance;
	}
	sf::Texture* loadTexture(std::string path, std::string name)
	{
		auto it = m_map.find(name);
		if (it != m_map.end())
		{
			return it->second;
		}
		else
		{
			sf::Texture* texture = new sf::Texture();
			if (texture->loadFromFile(path))
			{
				m_map.insert(std::make_pair(name, texture));
				return texture;
			}
			else
			{
                return nullptr;
			}
		}
	}
	sf::Texture* getTexture(std::string name)
	{
		auto it = m_map.find(name);
		if (it != m_map.end())
		{
			if (it->second == nullptr)
			{
				std::cout << "null texture\n";
			}
			return it->second;
		}
		else
		{
			std::cout << "Texture "<< name <<  " not found\n";
			return nullptr;
		}
	}
    void deleteTexture(std::string name)
    {
        auto it = m_map.find(name);
        if (it != m_map.end())
        {
            delete it->second;

            m_map.erase(name);
        }

        else
        {
            std::cout << "Texture" << name << " not deleted\n";

        }
    }
	void clearAll()
	{
		for (auto it : m_map)
		{
			delete it.second;
		}
		m_map.clear();
	}
private:
	ResourceManager()
	{
		loadTexture("textures/exitBtn_pressed.png", "default");

	}
	~ResourceManager()
	{
		clearAll();
	}

	static ResourceManager* m_instance;
	std::unordered_map<std::string, sf::Texture*> m_map;
};

#endif
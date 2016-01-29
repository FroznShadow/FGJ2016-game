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
				std::cout << "loaded texture" << path << " \n";
				return texture;
			}
			else
			{
				std::cout << "unable to load texture" << path << " \n";
			}
		}
	}
	sf::Texture* getTexture(std::string name)
	{
		auto it = m_map.find(name);
		if (it != m_map.end())
		{
			return it->second;
		}
		else
		{
			std::cout << "Texture not found\n";
			return nullptr;
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
		std::cout << "loading default texture\n";
		loadTexture("textures/default.png", "default");

	}
	~ResourceManager()
	{
		clearAll();
	}

	static ResourceManager* m_instance;
	std::unordered_map<std::string, sf::Texture*> m_map;
};

#endif
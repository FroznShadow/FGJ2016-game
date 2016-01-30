#pragma once

#include <SFML\Window\Mouse.hpp>

#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(int x, int y);
	virtual ~Button();
	virtual bool isHovering()=0;
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window)override;
protected:
	bool m_hovered;
};

Button::Button(int x, int y) : m_hovered(false), GameObject(sf::Vector2f(x, y)) {}

Button::~Button() {}

bool Button::isHovering() { return false; }

void Button::update(float deltaTime) { return; }

void Button::draw(sf::RenderWindow& window) { return; }

class RectangleButton : public Button
{
public:
	RectangleButton(int x, int y, int width, int height);
	~RectangleButton();

	bool isHovering();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	int m_width;
	int m_height;
	sf::RectangleShape m_rect;
};

RectangleButton::RectangleButton(int x, int y, int width, int height) : m_width(width), m_height(height), Button(x, y)
{
	m_rect = sf::RectangleShape(sf::Vector2f(width, height));
	m_rect.setFillColor(sf::Color::Blue);
	m_rect.setOrigin(m_width / 2, m_height / 2);
	m_rect.setPosition(x, y);
}

RectangleButton::~RectangleButton() {}

bool RectangleButton::isHovering() {
	return m_hovered;
}

void RectangleButton::update(float deltaTime) {}

void RectangleButton::draw(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	float _x = getPosition().x, _y = getPosition().y;
	if (_x - m_width / 2 < mousePos.x &&
		_x + m_width / 2 > mousePos.x &&
		_y + m_height / 2 > mousePos.y &&
		_y - m_height / 2 < mousePos.y) {
		m_rect.setFillColor(sf::Color::Blue);
		m_hovered = true;
	}
	else {
		m_rect.setFillColor(sf::Color::Green);
		m_hovered = false;
	}

	window.draw(m_rect);
}

class CircleButton : public Button
{
public:
	CircleButton(int x, int y, int radius);
	~CircleButton();

	bool isHovering();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	int m_radius;
};

CircleButton::CircleButton(int x, int y, int radius) : m_radius(radius), Button(x, y) {}

CircleButton::~CircleButton() {}

bool CircleButton::isHovering() {
	return m_hovered;
}

void CircleButton::update(float deltaTime) {}

void CircleButton::draw(sf::RenderWindow& window) 
{
	GameObject::draw(window);
	float _x = getPosition().x, _y = getPosition().y;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (m_radius*m_radius > pow(mousePos.x - _x - m_radius, 2) + pow(mousePos.y - _y - m_radius, 2)) {
		m_hovered = true;
	}
	else {
		m_hovered = false;
	}

	//window.draw(_circ);
}
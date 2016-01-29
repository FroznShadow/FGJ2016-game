#pragma once

#include <SFML\Window\Mouse.hpp>

#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(int x, int y);
	virtual ~Button();
	virtual bool isHovering()=0;
	virtual void M_update(float deltaTime);
	virtual void M_draw(sf::RenderWindow& window)override;
protected:
	bool _hovered;
};

Button::Button(int x, int y) : _hovered(false), GameObject(sf::Vector2f(x, y)) {}

Button::~Button() {}

bool Button::isHovering() { return false; }

void Button::M_update(float deltaTime) { return; }

void Button::M_draw(sf::RenderWindow& window) { return; }

class RectangleButton : public Button
{
public:
	RectangleButton(int x, int y, int width, int height);
	~RectangleButton();

	bool isHovering();
	void M_update(float deltaTime);
	void M_draw(sf::RenderWindow& window);
private:
	int _width;
	int _height;
	sf::RectangleShape _rect;
};

RectangleButton::RectangleButton(int x, int y, int width, int height) : _width(width), _height(height), Button(x, y)
{
	_rect = sf::RectangleShape(sf::Vector2f(width, height));
	_rect.setFillColor(sf::Color::Blue);
	_rect.setOrigin(_width / 2, _height / 2);
	_rect.setPosition(x, y);
}

RectangleButton::~RectangleButton() {}

bool RectangleButton::isHovering() {
	return _hovered;
}

void RectangleButton::M_update(float deltaTime) {}

void RectangleButton::M_draw(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	float _x = M_get_position().x, _y = M_get_position().y;
	if (_x - _width / 2 < mousePos.x &&
		_x + _width / 2 > mousePos.x &&
		_y + _height / 2 > mousePos.y &&
		_y - _height / 2 < mousePos.y) {
		_rect.setFillColor(sf::Color::Blue);
		_hovered = true;
	}
	else {
		_rect.setFillColor(sf::Color::Green);
		_hovered = false;
	}

	window.draw(_rect);
}

class CircleButton : public Button
{
public:
	CircleButton(int x, int y, int radius);
	~CircleButton();

	bool isHovering();
	void M_update(float deltaTime);
	void M_draw(sf::RenderWindow& window);
private:
	int _radius;
	sf::CircleShape _circ;
};

CircleButton::CircleButton(int x, int y, int radius) : _radius(radius), Button(x, y)
{
	_circ = sf::CircleShape(radius);
	_circ.setFillColor(sf::Color::Blue);
	_circ.setOrigin(radius, radius);
	_circ.setPosition(x, y);
}

CircleButton::~CircleButton() {}

bool CircleButton::isHovering() {
	return _hovered;
}

void CircleButton::M_update(float deltaTime) {}

void CircleButton::M_draw(sf::RenderWindow& window) 
{
	GameObject::M_draw(window);
	float _x = M_get_position().x, _y = M_get_position().y;
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (_radius*_radius > pow(mousePos.x - _x - _radius, 2) + pow(mousePos.y - _y - _radius, 2)) {
		_circ.setFillColor(sf::Color::Blue);
		_hovered = true;
	}
	else {
		_circ.setFillColor(sf::Color::Green);
		_hovered = false;
	}

	//window.draw(_circ);
}
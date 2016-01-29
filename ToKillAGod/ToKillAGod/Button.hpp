#pragma once

#include <SFML\Window\Mouse.hpp>

#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(int x, int y);
	virtual ~Button();
	virtual bool isHovering();
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
protected:
	int _x;
	int _y;
	bool _hovered;
};

Button::Button(int x, int y) : _x(x), _y(y), _hovered(false), GameObject(sf::Vector2f(x, y)) {}

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

void RectangleButton::update(float deltaTime) {}

void RectangleButton::draw(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
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
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
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

void CircleButton::update(float deltaTime) {}

void CircleButton::draw(sf::RenderWindow& window) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	if (_radius*_radius > pow(mousePos.x - _x, 2) + pow(mousePos.y - _y, 2)) {
		_circ.setFillColor(sf::Color::Blue);
		_hovered = true;
	}
	else {
		_circ.setFillColor(sf::Color::Green);
		_hovered = false;
	}

	window.draw(_circ);
}
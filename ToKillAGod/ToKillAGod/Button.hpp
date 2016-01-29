#pragma once

#include <SFML\System.hpp>
#include <SFML\Window\Mouse.hpp>

#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(int x, int y);
	virtual ~Button();
	virtual void pressed();
	virtual void update(float deltaTime);
protected:
	int _x;
	int _y;
	bool _hovered;
};

Button::Button(int x, int y) : _hovered(false), GameObject(sf::Vector2f(x, y)) {}

Button::~Button() {}

void Button::pressed() {}

void Button::update(float deltaTime) {}

class RectangleButton : public Button
{
public:
	RectangleButton(int x, int y, int width, int height);
	~RectangleButton();

	void pressed();
	void update(float deltaTime);
private:
	int _width;
	int _height;
};

RectangleButton::RectangleButton(int x, int y, int width, int height) : _width(width), _height(height), Button(x, y) {}

RectangleButton::~RectangleButton() {}

void RectangleButton::pressed() {
	//DoSomething();
}

void RectangleButton::update(float deltaTime) {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (_x - _width  / 2 < mousePos.x &&
		_x + _width  / 2 > mousePos.x &&
		_y + _height / 2 > mousePos.y &&
		_y - _height / 2 < mousePos.y) {
		_hovered = true;
	}
	else {
		_hovered = false;
	}
}

class CircleButton : public Button
{
public:
	CircleButton(int x, int y, int radius);
	~CircleButton();

	void pressed();
	void update(float deltaTime);
private:
	int _radius;
};

CircleButton::CircleButton(int x, int y, int radius) : _radius(radius), Button(x, y) {}

CircleButton::~CircleButton() {}

void CircleButton::pressed() {
	//DoSomething();
}

void CircleButton::update(float deltaTime) {
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (_radius*_radius > pow(mousePos.x - _x, 2) + pow(mousePos.y - _y, 2)) {
		_hovered = true;
	}
	else {
		_hovered = false;
	}
}
#pragma once

class Button
{
public:
	Button(int x, int y);
	virtual ~Button();
	virtual void pressed();
	virtual void update(float deltaTime);
private:
	int _x;
	int _y;
};

Button::Button(int x, int y) : _x(x), _y(y) {}

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

}

void RectangleButton::update(float deltaTime) {

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

}

void CircleButton::update(float deltaTime) {

}
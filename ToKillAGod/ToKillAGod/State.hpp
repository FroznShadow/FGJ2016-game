#pragma once

class State
{
public:
	State();
	virtual ~State();
	virtual void update();
};

State::State() {}

State::~State() {}

void update() {}
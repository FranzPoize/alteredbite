#pragma once

#include <memory>

#include "Player.h"
#include "ABInput.h"

class ControllableEntity
{
public:
	ControllableEntity(std::shared_ptr<Player> decoratedEntity,std::shared_ptr<ABInput> inputComponent);
	void update();
	bool getJumpState();
	void inputUpdate(bool left,bool right,bool jump);
	void draw();
	~ControllableEntity();
protected:
	int xspeed;
	int yspeed;
	bool jumpState;
	std::shared_ptr<Player> decoratedEntity;
	static const int AB_SPEED = 90;
	std::shared_ptr<ABInput> inputComponent;
};
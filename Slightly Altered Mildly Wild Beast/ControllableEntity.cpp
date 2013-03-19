#include <Windows.h>
#include "ControllableEntity.h"

bool ControllableEntity::getJumpState()
{
	return jumpState;
}

ControllableEntity::ControllableEntity(std::shared_ptr<Player> decoratedEntity,std::shared_ptr<ABInput> inputComponent)
{
	this->decoratedEntity = decoratedEntity;
	this->inputComponent = inputComponent;
	xspeed = 0.0f;
	yspeed = 0.0f;
}

ControllableEntity::~ControllableEntity()
{
	this->decoratedEntity.reset();
	this->inputComponent.reset();
}

void ControllableEntity::update()
{
	inputComponent->update(*this);
	decoratedEntity->move(xspeed,yspeed);
	decoratedEntity->update();

}

void ControllableEntity::draw()
{
	decoratedEntity->draw();
}

void ControllableEntity::inputUpdate(bool left,bool right,bool jump)
{
	if(left) xspeed = -AB_SPEED/20;
	else if(right) xspeed = AB_SPEED/20;
	else xspeed = 0.0f;

	if(jump) yspeed = -AB_SPEED/10;
	else yspeed = 0.0f;
}
#pragma once
#include <memory>

#include "ABXBoxController.h"

class ControllableEntity;
class ABInput
{
public:
	ABInput(std::shared_ptr<ABXBoxController> controller);
	void update(ControllableEntity& entity);
	~ABInput();
private:
	std::shared_ptr<ABXBoxController> controller;
};
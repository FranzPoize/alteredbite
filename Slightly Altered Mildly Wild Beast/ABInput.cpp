#include <Windows.h>
#include <XInput.h>
#include <math.h>

#include "ABInput.h"
#include "ControllableEntity.h"
#include "ABXBoxController.h"

ABInput::ABInput(std::shared_ptr<ABXBoxController> controller)
{
	this->controller = controller;
}

ABInput::~ABInput()
{
	this->controller.reset();
}

void ABInput::update(ControllableEntity& entity)
{
	XINPUT_STATE state;
	if (controller->IsConnected())
	{
		state = controller->GetState();
		float LX = state.Gamepad.sThumbLX;
		float LY = state.Gamepad.sThumbLY;

		//determine how far the controller is pushed
		float lMagnitude = sqrt(LX*LX + LY*LY);

		//check if the controller is outside a circular dead zone
		if (lMagnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
		  //clip the lMagnitude at its expected maximum value
		  if (lMagnitude > 32767) lMagnitude = 32767;
  
		  //adjust lMagnitude relative to the end of the dead zone
		  lMagnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		}
		else //if the controller is in the deadzone zero out the lMagnitude
		{
			lMagnitude = 0.0;
		}

		bool left = false;
		bool right = false;
		bool jump = false;

		if (LX < 0 && lMagnitude > 0) left = true;
		else if (LX > 0 && lMagnitude > 0) right = true;
		else 
		{
			left = false;
			right = false;
		}



		WORD buttons = state.Gamepad.wButtons;
		jump = buttons & XINPUT_GAMEPAD_A;

		entity.inputUpdate(left,right,jump);
	}
}
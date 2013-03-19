#include <Windows.h>
#include <XInput.h>
#include "ABXBoxController.h"
#include "ABProjectile.h"

ABXBoxController::ABXBoxController()
{
	_controllerNum = 0;
}

XINPUT_STATE ABXBoxController::GetState()
{
	ZeroMemory( &_controllerState, sizeof(XINPUT_STATE) );

	DWORD dwResult = XInputGetState(_controllerNum,&_controllerState);
	if (dwResult == ERROR_SUCCESS) return _controllerState;
}

bool ABXBoxController::IsConnected()
{
	ZeroMemory( &_controllerState, sizeof(XINPUT_STATE) );

	DWORD dwResult = XInputGetState(_controllerNum,&_controllerState);
	return dwResult == ERROR_SUCCESS;
}

void ABXBoxController::Vibrate(int leftVal, int rightVal)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
	vibration.wLeftMotorSpeed = leftVal;
	vibration.wRightMotorSpeed = rightVal;
	XInputSetState( _controllerNum, &vibration );
}
#pragma once
#include <XInput.h>

#pragma comment(lib,"XInput.lib")
class ABXBoxController
{
private:
    XINPUT_STATE _controllerState;
    int _controllerNum;
public:
    ABXBoxController();
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};
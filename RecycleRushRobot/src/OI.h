#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick* driverJoystick;
	Joystick* pickerJoystick;

	// TODO - Define joystick buttons

	Joystick* GetDriverJoystick() { return driverJoystick; }

public:
	OI();

	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();
};

#endif

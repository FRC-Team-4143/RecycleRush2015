#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();

	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();

	float GetBinArmAxisValue();
	float GetBinElevatorAxisValue();
	float GetToteElevatorAxisValue();

private:
	// Declare joysticks
	Joystick* driverJoystick;
	Joystick* pickerJoystick;

	// Declare commands
	Command* rotateLeft90;
	Command* rotateRight90;
	Command* goUp;
	Command* goDown;

	// Declare joystick buttons
	// TODO

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

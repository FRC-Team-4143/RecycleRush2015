#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();

	float GetJoystickX();
	float GetJoystickY();
	float GetJoystickZ();

	float GetDriverLeftTrigger();
	float GetDriverRightTrigger();

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
	Command* Tote1Up;
	Command* Tote1Down;
	Command* Tote2Up;
	Command* Tote2Down;
	Command* Tote3Up;
	Command* Tote3Down;
	//Command* BinUp;
	//Command* BinDown;
	Command* binArmIn;
	Command* binArmOut;
	Command* binUp;
	Command* binDown;

	// Declare joystick buttons
	// TODO

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

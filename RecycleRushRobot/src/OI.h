#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();

	bool GetButtonB();

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

	Preferences* prefs;

	// Declare commands
	Command* rotateLeft90;
	Command* rotateRight90;
	Command* Tote1Up;
	Command* Tote1Down;
	Command* Tote2Up;
	Command* Tote2Down;
	Command* Tote3Up;
	Command* Tote3Down;
	Command* binArmIn;
	Command* binArmOut;
	Command* switchCamera;
	Command* testSolenoidForward;
	Command* testSolenoidReverse;
	Command* clawRoutine;
	Command* runCamera;

	// Declare joystick buttons
	// TODO

	Joystick* GetDriverJoystick() { return driverJoystick; }
	Joystick* GetPickerJoystick() { return pickerJoystick; }
};

#endif

#include "OI.h"

OI::OI()
{
	driverJoystick = new Joystick(0);
	pickerJoystick = new Joystick(1);

	// TODO - Add joystick button mappings
	// TODO - Add SmartDashboard controls
}

const float JOYSTICK_DEAD_ZONE = 0.15;

float OI::GetJoystickX() {
	float x = GetDriverJoystick()->GetRawAxis(0); // TODO - Define a constant for this axis
	return (fabs(x) < JOYSTICK_DEAD_ZONE) ? 0 : x;
}

float OI::GetJoystickY() {
	float x = GetDriverJoystick()->GetRawAxis(1); // TODO - Define a constant for this axis
	return (fabs(x) < JOYSTICK_DEAD_ZONE) ? 0 : x;
}

float OI::GetJoystickZ() {
	float x = GetDriverJoystick()->GetRawAxis(4); // TODO - Define a constant for this axis
	return (fabs(x) < JOYSTICK_DEAD_ZONE) ? 0 : x;
}

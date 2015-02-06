#include "Logger.h"
#include "OI.h"
#include "Commands/FixPrefs.h"
#include "Commands/RotateBy.h"
#include "Commands/SaveWheelPositions.h"
#include "Commands/ShowPrefs.h"
#include "Commands/UpdateSmartDashboard.h"

const uint32_t JOYSTICK_PORT_DRIVER = 0;
const uint32_t JOYSTICK_PORT_PICKER = 1;

const float JOYSTICK_DEAD_ZONE = 0.15;

const uint32_t JOYSTICK_LX_AXIS    = 0;
const uint32_t JOYSTICK_LY_AXIS    = 1;
const uint32_t JOYSTICK_LTRIG_AXIS = 2;
const uint32_t JOYSTICK_RTRIG_AXIS = 3;
const uint32_t JOYSTICK_RX_AXIS    = 4;
const uint32_t JOYSTICK_RY_AXIS    = 5;

const uint32_t JOYSTICK_BUTTON_A     = 1;
const uint32_t JOYSTICK_BUTTON_B     = 2;
const uint32_t JOYSTICK_BUTTON_X     = 3;
const uint32_t JOYSTICK_BUTTON_Y     = 4;
const uint32_t JOYSTICK_BUTTON_LB    = 5;
const uint32_t JOYSTICK_BUTTON_RB    = 6;
const uint32_t JOYSTICK_BUTTON_BACK  = 7;
const uint32_t JOYSTICK_BUTTON_START = 8;

OI::OI() {
	LOG("OI::OI");

	// Define joysticks
	driverJoystick = new Joystick(JOYSTICK_PORT_DRIVER);
	pickerJoystick = new Joystick(JOYSTICK_PORT_PICKER);

	// Define commands
	rotateLeft90 = new RotateBy("Rotate Left 90", -90);
	rotateRight90 = new RotateBy("Rotate Right 90", 90);

	// Define joystick button mappings
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(rotateLeft90);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(rotateRight90);

	// Add SmartDashboard controls
	SmartDashboard::PutData("FixPrefs", new FixPrefs());
	SmartDashboard::PutData("SaveWheelPositions", new SaveWheelPositions());
	SmartDashboard::PutData("ShowPrefs", new ShowPrefs());
	SmartDashboard::PutData("UpdateSmartDashboard", new UpdateSmartDashboard());
	SmartDashboard::PutData("Rotate Left 90", rotateLeft90);
	SmartDashboard::PutData("Rotate Right 90", rotateRight90);

	SmartDashboard::PutNumber("Auto-Drive-Speed", 0.5);
	SmartDashboard::PutNumber("Auto-Drive-Time", 1.0);
}

float OI::GetJoystickX() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_LX_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickY() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_LY_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickZ() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_RX_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

#include "OI.h"
#include "Commands/RotateBy.h"
#include "Commands/SetWheelOffsets.h"
#include "Commands/UpdateSmartDashboard.h"

const uint32_t JOYSTICK_PORT_DRIVER = 0;
const uint32_t JOYSTICK_PORT_PICKER = 1;

const float JOYSTICK_DEAD_ZONE = 0.15;

const uint32_t JOYSTICK_X_AXIS = 0;
const uint32_t JOYSTICK_Y_AXIS = 1;
const uint32_t JOYSTICK_Z_AXIS = 4;

const uint32_t JOYSTICK_BUTTON_LB = 4;
const uint32_t JOYSTICK_BUTTON_RB = 5;

OI::OI() {
	std::cout << "OI::OI" << std::endl;

	// Define joysticks
	driverJoystick = new Joystick(JOYSTICK_PORT_DRIVER);
	pickerJoystick = new Joystick(JOYSTICK_PORT_PICKER);

	// Define commands
//	rotateLeft90 = new RotateBy("Rotate Left 90", -90);
//	rotateRight90 = new RotateBy("Rotate Right 90", 90);

	// Define joystick button mappings
//	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(rotateLeft90);
//	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(rotateRight90);

	// Add SmartDashboard controls
	// TODO
	SmartDashboard::PutData("SchedulerData", Scheduler::GetInstance());
	SmartDashboard::PutData("SetWheelOffsets", new SetWheelOffsets());
	SmartDashboard::PutData("UpdateSmartDashboard", new UpdateSmartDashboard());
//	SmartDashboard::PutData("Rotate Left 90", rotateLeft90);
//	SmartDashboard::PutData("Rotate Right 90", rotateRight90);
}

float OI::GetJoystickX() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_X_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickY() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_Y_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetJoystickZ() {
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_Z_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

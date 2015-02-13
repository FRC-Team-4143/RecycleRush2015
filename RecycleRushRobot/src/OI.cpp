#include "Logger.h"
#include "OI.h"
#include "Robot.h"
#include "Commands/FixPrefs.h"
#include "Commands/GyroSquare.h"
#include "Commands/RotateBy.h"
#include "Commands/SaveWheelPositions.h"
#include "Commands/ShowPrefs.h"
#include "Commands/UpdateSmartDashboard.h"
#include "Commands/LowerElevator.h"
#include "Commands/RaiseElevator.h"
#include "Commands/ResetAllEncoders.h"
#include "Commands/BinArmIn.h"
#include "Commands/BinArmOut.h"
#include "Commands/BinUp.h"
#include "Commands/BinDown.h"

const uint32_t JOYSTICK_PORT_DRIVER = 0;
const uint32_t JOYSTICK_PORT_PICKER = 1;

const float JOYSTICK_DEAD_ZONE = 0.1;

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


	//Tote1Up = new RaiseElevator(Robot::toteElevator1);
	//Tote1Down = new LowerElevator(Robot::toteElevator1);

	//Tote2Up = new RaiseElevator(Robot::toteElevator2);
	//Tote2Down = new LowerElevator(Robot::toteElevator2);

	//Tote3Up = new RaiseElevator(Robot::toteElevator3);
	//Tote3Down = new LowerElevator(Robot::toteElevator3);

	//BinUp = new RaiseElevator(Robot::binElevator);
	//BinDown = new LowerElevator(Robot::binElevator);

	binArmIn = new BinArmIn();
	binArmOut = new BinArmOut();

	binUp = new BinUp();
	binDown = new BinDown();


	// Define joystick button mappings
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(rotateLeft90);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(rotateRight90);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_A))->WhenPressed(Tote1Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_B))->WhenPressed(Tote1Down);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_X))->WhenPressed(Tote2Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_Y))->WhenPressed(Tote2Down);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(Tote3Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(Tote3Down);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhenPressed(BinUp);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhenPressed(BinDown);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhileHeld(binArmIn);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhileHeld(binArmOut);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhileHeld(binUp);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhileHeld(binDown);

	// Add SmartDashboard controls
	SmartDashboard::PutData("FixPrefs", new FixPrefs());
	SmartDashboard::PutData("SaveWheelPositions", new SaveWheelPositions());
	SmartDashboard::PutData("ShowPrefs", new ShowPrefs());
	SmartDashboard::PutData("UpdateSmartDashboard", new UpdateSmartDashboard());
	SmartDashboard::PutData("Rotate Left 90", rotateLeft90);
	SmartDashboard::PutData("Rotate Right 90", rotateRight90);

	SmartDashboard::PutNumber("Auto-Drive-Speed", 0.5);
	SmartDashboard::PutNumber("Auto-Drive-Time", 1.0);
	SmartDashboard::PutData("Gyro Square", new GyroSquare());
	SmartDashboard::PutData("Reset All Encoders", new ResetAllEncoders());

	SmartDashboard::PutNumber("pdp-channel", 0);
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

float OI::GetDriverRightTrigger(){
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_RTRIG_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetDriverLeftTrigger(){
	auto value = GetDriverJoystick()->GetRawAxis(JOYSTICK_LTRIG_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : value;
}

float OI::GetBinArmAxisValue() {
	auto value = GetPickerJoystick()->GetRawAxis(JOYSTICK_LTRIG_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : -value;
}

float OI::GetBinElevatorAxisValue() {
	auto value = GetPickerJoystick()->GetRawAxis(JOYSTICK_RY_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : -value;
}

float OI::GetToteElevatorAxisValue() {
	auto value = GetPickerJoystick()->GetRawAxis(JOYSTICK_LY_AXIS);
	return (fabs(value) < JOYSTICK_DEAD_ZONE) ? 0 : -value;
}

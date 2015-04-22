#include "Commands/ClampClaw.h"
#include "Commands/ReleaseClaw.h"
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
#include "Commands/ArmIn.h"
#include "Commands/ArmOut.h"
#include "Commands/CompleteElevatorDefaultCommand.h"
#include "Commands/SwitchCamera.h"
#include "Commands/SetElevatorDistances.h"
#include "Commands/LowerAllElevators.h"
#include "Commands/ClawRoutine.h"
#include "Commands/ResetArm.h"
#include "Commands/RunCamera.h"
#include "Commands/SwitchMode.h"
#include "Commands/Raise1Level.h"
#include "Commands/CycleLightMode.h"
#include "Commands/CompleteLower.h"
#include "Commands/ToggleSqueezeMode.h"
#include "Commands/PlaceStack.h"
#include "Commands/ScriptValidate.h"
#include "Commands/GyroCrab.h"
#include "Commands/ResetGyro.h"
#include "Commands/BurglarUp.h"
#include "Commands/BurglarDown.h"
#include "Commands/BurglarOff.h"

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
const uint32_t JOYSTICK_BUTTON_LEFT  = 9;
const uint32_t JOYSTICK_BUTTON_RIGHT = 10;

OI::OI() {
	LOG("OI::OI");

	// Define joysticks
	driverJoystick = new Joystick(JOYSTICK_PORT_DRIVER);
	pickerJoystick = new Joystick(JOYSTICK_PORT_PICKER);

	//prefs = Preferences::GetInstance();

	// Define commands
	//rotateLeft90 = new RotateBy("Rotate Left 90", -90);
	//rotateRight90 = new RotateBy("Rotate Right 90", 90);


	//Tote1Up = new RaiseElevator(Robot::toteElevator1);
	//Tote1Down = new LowerElevator(Robot::toteElevator1);

	//Tote2Up = new RaiseElevator(Robot::toteElevator2);
	//Tote2Down = new LowerElevator(Robot::toteElevator2);

	//Tote3Up = new RaiseElevator(Robot::toteElevator3);
	//Tote3Down = new LowerElevator(Robot::toteElevator3);

	//BinUp = new RaiseElevator(Robot::binElevator);
	//BinDown = new LowerElevator(Robot::binElevator);

	binArmIn = new ArmIn();
	binArmOut = new ArmOut();
	//switchCamera = new SwitchCamera();
	testSolenoidForward = new ClampClaw();
	testSolenoidReverse = new ReleaseClaw();
	clawRoutine = new ClawRoutine();
	//runCamera = new RunCamera(0);
	switchMode = new SwitchMode();
	raise1Level = new Raise1Level();
	cycleLightMode = new CycleLightMode();
	completeLower = new CompleteLower();
	toggleSqueezeMode = new ToggleSqueezeMode();
	placeStack = new PlaceStack();
	gyroCrab = new GyroCrab();


	// Define joystick button mappings
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(rotateLeft90);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(rotateRight90);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_A))->WhenPressed(Tote1Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_B))->WhenPressed(Tote1Down);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_X))->WhenPressed(Tote2Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_Y))->WhenPressed(Tote2Down);

	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhenPressed(Tote3Up);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhenPressed(Tote3Down);

	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RB))->WhileHeld(binArmOut);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_LB))->WhileHeld(binArmIn);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhenPressed(switchCamera);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_X))->WhileHeld(testSolenoidForward);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_Y))->WhileHeld(testSolenoidReverse);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhenPressed(clawRoutine);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_A))->WhileHeld(runCamera);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_START))->WhenPressed(switchMode);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_BACK))->WhenPressed(cycleLightMode);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_A))->WhenPressed(raise1Level);
	//(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_Y))->WhenPressed(completeLower);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_X))->WhenPressed(toggleSqueezeMode);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_B))->WhenPressed(placeStack);
	(new JoystickButton(driverJoystick, JOYSTICK_BUTTON_RIGHT))->WhileHeld(gyroCrab);

	// Add SmartDashboard controls
	//SmartDashboard::PutNumber("Tote4-3 distance", prefs->GetDouble("distance4_3"));
	//SmartDashboard::PutNumber("Tote3-2 distance", prefs->GetDouble("distance3_2"));
	//SmartDashboard::PutNumber("Tote2-1 distance", prefs->GetDouble("distance2_1"));
	//SmartDashboard::PutNumber("Tote4-max", 62);
	//SmartDashboard::PutNumber("Tote3-max", 60);
	//SmartDashboard::PutNumber("Tote2-max", 58);
	//SmartDashboard::PutNumber("Tote1-max", 56);

	SmartDashboard::PutData("Save Elevator Preference", new SetElevatorDistances());

	//SmartDashboard::PutData("Lower All Elevators", new LowerAllElevators());
	//SmartDashboard::PutData("Reset Arm", new ResetArm());
	SmartDashboard::PutData("Reset All Encoders", new ResetAllEncoders());

	//SmartDashboard::PutData("Clamp Claw", new ClampClaw());
	//SmartDashboard::PutData("Release Claw", new ReleaseClaw());
	//SmartDashboard::PutData("FixPrefs", new FixPrefs());
	SmartDashboard::PutData("SaveWheelPositions", new SaveWheelPositions());
	//SmartDashboard::PutData("ShowPrefs", new ShowPrefs());
	SmartDashboard::PutData("UpdateSmartDashboard", new UpdateSmartDashboard());
	//SmartDashboard::PutData("Rotate Left 90", rotateLeft90);
	//SmartDashboard::PutData("Rotate Right 90", rotateRight90);

	//SmartDashboard::PutNumber("Auto-Drive-Speed", 0.5);
	//SmartDashboard::PutNumber("Auto-Drive-Time", 1.0);
	//SmartDashboard::PutData("Gyro Square", new GyroSquare());
	//SmartDashboard::PutNumber("Gyro-speed", 0.5);
	//SmartDashboard::PutNumber("Gyro-time", 1);

	//SmartDashboard::PutNumber("pdp-channel", 0);
	//SmartDashboard::PutNumber("pdp Total Voltage", RobotMap::pdp->GetVoltage());
	//SmartDashboard::PutNumber("pdp current channel reading", RobotMap::pdp->GetCurrent(0));

	//SmartDashboard::PutData("Run Camera", runCamera);

	SmartDashboard::PutData("Validate Script", new ScriptValidate());

	SmartDashboard::PutData("Reset Gyro Yaw", new ResetGyro());

	SmartDashboard::PutData("Burglar Up", new BurglarUp());
	SmartDashboard::PutData("Burglar Down", new BurglarDown());
	SmartDashboard::PutData("Burglar Off", new BurglarOff());
}

bool OI::GetButtonA(){
	auto value = GetDriverJoystick()->GetRawButton(JOYSTICK_BUTTON_A);
	return (value);
}

bool OI::GetButtonB(){
	auto value = GetDriverJoystick()->GetRawButton(JOYSTICK_BUTTON_B);
	return (value);
}

bool OI::GetButtonX(){
	auto value = GetDriverJoystick()->GetRawButton(JOYSTICK_BUTTON_X);
	return (value);
}

bool OI::GetButtonY(){
	auto value = GetDriverJoystick()->GetRawButton(JOYSTICK_BUTTON_Y);
	return (value);
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

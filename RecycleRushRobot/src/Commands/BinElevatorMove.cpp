#include "BinElevatorMove.h"
#include "../Robot.h"

// ==========================================================================

BinElevatorMove::BinElevatorMove() : Command("Bin Elevator Move") {
	std::cout << "BinElevatorMove::ctor" << std::endl;

	Requires(Robot::binElevator);
}

// ==========================================================================
// Called just before this Command runs the first time

void BinElevatorMove::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void BinElevatorMove::Execute() {
	// Get joystick axis value
	auto axisValue = Robot::oi->GetBinElevatorAxisValue();
	auto inches = AxisToInches(axisValue);
	// TODO - Call binElevator method to move up/down based on axis
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool BinElevatorMove::IsFinished() {
	return false;
}

// ==========================================================================
// Called once after isFinished returns true

void BinElevatorMove::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void BinElevatorMove::Interrupted() {
	End();
}

// ==========================================================================

float BinElevatorMove::AxisToInches(float axisValue) {
	// Do any necessary scaling here
	return axisValue;
}

// ==========================================================================

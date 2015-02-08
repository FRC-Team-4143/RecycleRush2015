#include "ToteElevatorGroupMove.h"
#include "../Robot.h"

// ==========================================================================

ToteElevatorGroupMove::ToteElevatorGroupMove() : Command("Tote Elevator Group Move") {
	std::cout << "ToteElevatorGroupMove::ctor" << std::endl;

	Requires(Robot::toteElevatorGroup);
}

// ==========================================================================
// Called just before this Command runs the first time

void ToteElevatorGroupMove::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void ToteElevatorGroupMove::Execute() {
	auto axisValue = Robot::oi->GetToteElevatorAxisValue();
	auto inches = AxisToInches(axisValue);
	if (inches > 0) {
		Robot::toteElevatorGroup->MoveUp(inches);
	}
	else {
		Robot::toteElevatorGroup->MoveDown(-inches);
	}
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool ToteElevatorGroupMove::IsFinished() {
	return false;
}

// ==========================================================================
// Called once after isFinished returns true

void ToteElevatorGroupMove::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void ToteElevatorGroupMove::Interrupted() {
	End();
}

// ==========================================================================

float ToteElevatorGroupMove::AxisToInches(float axisValue) {
	// Do any necessary scaling here
	return axisValue * 4;
}

// ==========================================================================

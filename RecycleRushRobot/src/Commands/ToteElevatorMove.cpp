#include "ToteElevatorMove.h"
#include "../Robot.h"

// ==========================================================================

ToteElevatorMove::ToteElevatorMove() : Command("Tote Elevator Move") {
	std::cout << "ToteElevatorMove::ctor" << std::endl;

	Requires(Robot::toteElevator1);
}

// ==========================================================================
// Called just before this Command runs the first time

void ToteElevatorMove::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void ToteElevatorMove::Execute() {
	auto axisValue = Robot::oi->GetToteElevatorAxisValue();
	auto inches = AxisToInches(axisValue);
	if (inches > 0) {
		Robot::toteElevator1->MoveUp(inches);
	}
	else {
		Robot::toteElevator1->MoveDown(-inches);
	}
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool ToteElevatorMove::IsFinished() {
	return false;
}

// ==========================================================================
// Called once after isFinished returns true

void ToteElevatorMove::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void ToteElevatorMove::Interrupted() {
	End();
}

// ==========================================================================

float ToteElevatorMove::AxisToInches(float axisValue) {
	// Do any necessary scaling here
	return axisValue;
}

// ==========================================================================

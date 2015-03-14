#include "BinArmMove.h"
#include "../Robot.h"

// ==========================================================================

BinArmMove::BinArmMove() : Command("Bin Arm Move") {
	std::cout << "BinArmMove::ctor" << std::endl;

	Requires(Robot::binArm);
}

// ==========================================================================
// Called just before this Command runs the first time

void BinArmMove::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void BinArmMove::Execute() {
	auto axisValue = Robot::oi->GetBinArmAxisValue();
	Robot::binArm->Move(axisValue);
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool BinArmMove::IsFinished() {
	return false;
}

// ==========================================================================
// Called once after isFinished returns true

void BinArmMove::End() {
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void BinArmMove::Interrupted() {
	End();
}

// ==========================================================================

#include "BinArmIn.h"
#include "../RobotMap.h"

BinArmIn::BinArmIn()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void BinArmIn::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BinArmIn::Execute()
{
	RobotMap::binArmMotor->Set(-1);
}

// Make this return true when this Command no longer needs to run execute()
bool BinArmIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BinArmIn::End()
{
	RobotMap::binArmMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinArmIn::Interrupted()
{
	RobotMap::binArmMotor->Set(0);
}

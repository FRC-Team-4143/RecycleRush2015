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
	arm = RobotMap::binArmPID;
	setpoint = arm->GetSetpoint();
	arm->SetSetpoint(std::max((float)0, setpoint - 3));
	//RobotMap::binArmMotor->Set(-0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool BinArmIn::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BinArmIn::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinArmIn::Interrupted()
{

}

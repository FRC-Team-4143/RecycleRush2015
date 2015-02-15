#include "BinArmOut.h"
#include "../RobotMap.h"


BinArmOut::BinArmOut(double distance)
{
	setpoint = RobotMap::binArmPID->GetSetpoint() + distance;
}

// Called just before this Command runs the first time
void BinArmOut::Initialize()
{
	arm = RobotMap::binArmPID;
	arm->SetSetpoint(setpoint);
	arm->Enable();
}

// Called repeatedly when this Command is scheduled to run
void BinArmOut::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool BinArmOut::IsFinished()
{
	return arm->OnTarget();
}

// Called once after isFinished returns true
void BinArmOut::End()
{
	arm->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinArmOut::Interrupted()
{
	arm->Disable();
}

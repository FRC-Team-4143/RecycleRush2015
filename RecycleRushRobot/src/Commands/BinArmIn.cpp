#include "BinArmIn.h"
#include "../RobotMap.h"

BinArmIn::BinArmIn(double distance)
{
	setpoint = RobotMap::binArmPID->GetSetpoint() + distance;
}

// Called just before this Command runs the first time
void BinArmIn::Initialize()
{
	arm = RobotMap::binArmPID;
	arm->SetSetpoint(setpoint);
	arm->Enable();
}

// Called repeatedly when this Command is scheduled to run
void BinArmIn::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool BinArmIn::IsFinished()
{
	return arm->OnTarget();
}

// Called once after isFinished returns true
void BinArmIn::End()
{
	arm->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinArmIn::Interrupted()
{
	arm->Disable();
}

#include "BinArmIn.h"
#include "../RobotMap.h"

BinArmIn::BinArmIn()
{
	setpoint = NULL;
}

BinArmIn::BinArmIn(double distance)
{
	setpoint = RobotMap::binArmPID->GetSetpoint() + distance;
}

// Called just before this Command runs the first time
void BinArmIn::Initialize()
{
	arm = RobotMap::binArmPID;
}

// Called repeatedly when this Command is scheduled to run
void BinArmIn::Execute()
{

	if (setpoint != NULL){
		arm->SetSetpoint(setpoint);
	} else {
		current = arm->GetSetpoint();
		arm->SetSetpoint(std::max((double)0, current - 3));
	}



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

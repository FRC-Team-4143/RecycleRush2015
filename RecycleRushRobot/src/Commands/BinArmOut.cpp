#include "BinArmOut.h"
#include "../RobotMap.h"

BinArmOut::BinArmOut()
{
	setpoint = NULL;
}

BinArmOut::BinArmOut(double distance)
{
	setpoint = RobotMap::binArmPID->GetSetpoint() + distance;
}

// Called just before this Command runs the first time
void BinArmOut::Initialize()
{
	arm = RobotMap::binArmPID;
}

// Called repeatedly when this Command is scheduled to run
void BinArmOut::Execute()
{
	if (setpoint != NULL){
		arm->SetSetpoint(setpoint);
	} else {
		current = arm->GetSetpoint();
		arm->SetSetpoint(std::min((double)1080, current + 3));
	}

	//RobotMap::binArmMotor->Set(0.5);
}

// Make this return true when this Command no longer needs to run execute()
bool BinArmOut::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BinArmOut::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BinArmOut::Interrupted()
{

}

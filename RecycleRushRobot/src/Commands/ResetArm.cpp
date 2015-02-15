#include "ResetArm.h"
#include "../RobotMap.h"

ResetArm::ResetArm()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	SetTimeout(3);
}

// Called just before this Command runs the first time
void ResetArm::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ResetArm::Execute()
{
	while(RobotMap::pdp->GetCurrent(0/*GET PDP PORT*/) < 5 && !IsTimedOut()){
		RobotMap::binArmMotor->Set(-0.5);
	}
	RobotMap::binArmMotor->Set(0);
	RobotMap::binArmPos->Reset();
	RobotMap::binArmPID->SetSetpoint(0);

}

// Make this return true when this Command no longer needs to run execute()
bool ResetArm::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ResetArm::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetArm::Interrupted()
{

}

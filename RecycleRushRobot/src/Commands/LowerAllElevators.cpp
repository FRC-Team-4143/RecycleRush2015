#include "LowerAllElevators.h"
#include "RobotMap.h"

LowerAllElevators::LowerAllElevators()
{
	motor1 = RobotMap::toteElevator1Motor;
	motor2 = RobotMap::toteElevator2Motor;
	motor3 = RobotMap::toteElevator3Motor;
	motor4 = RobotMap::toteElevator4Motor;
	pdp = RobotMap::pdp;
}

// Called just before this Command runs the first time
void LowerAllElevators::Initialize()
{
	SetTimeout(10);
}

// Called repeatedly when this Command is scheduled to run
void LowerAllElevators::Execute()
{
	while(pdp->GetCurrent(15) < 5 && !IsTimedOut()){
		motor1->Set(-0.5);
	}
	motor1->Set(0);
	RobotMap::toteElevator1Pos->Reset();
	RobotMap::toteElevator1PID->SetSetpoint(0);

	while(pdp->GetCurrent(5) < 5 && !IsTimedOut()){
		motor2->Set(-0.5);
	}
	motor2->Set(0);
	RobotMap::toteElevator2Pos->Reset();
	RobotMap::toteElevator2PID->SetSetpoint(0);

	while(pdp->GetCurrent(8) < 5 && !IsTimedOut()){
		motor3->Set(-0.5);
	}
	motor3->Set(0);
	RobotMap::toteElevator3Pos->Reset();
	RobotMap::toteElevator3PID->SetSetpoint(0);

	while(pdp->GetCurrent(0) < 5 && !IsTimedOut()){
		motor4->Set(-0.5);
	}
	motor4->Set(0);
	RobotMap::toteElevator4Pos->Reset();
	RobotMap::toteElevator4PID->SetSetpoint(0);

}

// Make this return true when this Command no longer needs to run execute()
bool LowerAllElevators::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void LowerAllElevators::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerAllElevators::Interrupted()
{

}

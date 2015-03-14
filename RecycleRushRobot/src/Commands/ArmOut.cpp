#include "ArmOut.h"
#include "../RobotMap.h"
#include "../Robot.h"

ArmOut::ArmOut() {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::binArm);
}

// Called just before this Command runs the first time
void ArmOut::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ArmOut::Execute() {
	//if (RobotMap::binArmPos >= 0){
#if USE_BINARMSUB
	Robot::binArm->Move(1);
#else
	RobotMap::binArmMotor->Set(1);
#endif
	//} else {
	//	RobotMap::binArmMotor->Set(0);
	//}

//float current = RobotMap::binArmPos->Get();
//float setpoint = current + 15;
//RobotMap::binArmPID->SetSetpoint(std::min((float)(30*30), setpoint));
}

// Make this return true when this Command no longer needs to run execute()
bool ArmOut::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ArmOut::End() {
	RobotMap::binArmMotor->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmOut::Interrupted() {
	RobotMap::binArmMotor->Set(0);
}

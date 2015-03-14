#include "UpdateSmartDashboard.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include <WPILib.h>

// ==========================================================================

UpdateSmartDashboard::UpdateSmartDashboard() : Command("Update SmartDashboard") {
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void UpdateSmartDashboard::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void UpdateSmartDashboard::Execute() {

	//pdpCurrentChannel = SmartDashboard::GetNumber("pdp-channel");

	//SmartDashboard::PutData("SchedulerData", Scheduler::GetInstance());

	SmartDashboard::PutNumber("Encoder0 tote1", RobotMap::toteElevator1Pos->GetDistance());
	SmartDashboard::PutNumber("Encoder2 tote2", RobotMap::toteElevator2Pos->GetDistance());
	SmartDashboard::PutNumber("Encoder4 tote3", RobotMap::toteElevator3Pos->GetDistance());
	SmartDashboard::PutNumber("Encoder6 tote4", RobotMap::toteElevator4Pos->GetDistance());
	SmartDashboard::PutNumber("Encoder8 arm", RobotMap::binArmPos->GetDistance());
	SmartDashboard::PutNumber("elevator setpoint", Robot::completeElevator->setpoint);

	SmartDashboard::PutNumber("Gyro-Calibrating", Robot::gyroSub->IsCalibrating());
	SmartDashboard::PutNumber("Gyro-Yaw", Robot::gyroSub->PIDGet());

	//double x, y;
	//Robot::mouseSubsystem->GetPosition(x, y);
	//SmartDashboard::PutNumber("mouse X", x);
	//SmartDashboard::PutNumber("mouse Y", y);
	double vision = Robot::visionBridge->GetPosition();
	SmartDashboard::PutNumber("visionbridge", vision);

	//SmartDashboard::PutNumber("Driver-X", Robot::oi->GetJoystickX());
	//SmartDashboard::PutNumber("Driver-Y", Robot::oi->GetJoystickY());
	//SmartDashboard::PutNumber("Driver-Z", Robot::oi->GetJoystickZ());

	//SmartDashboard::PutNumber("FL-Drive-Output", Robot::driveTrain->frontLeftDrive->Get());
	//SmartDashboard::PutNumber("FR-Drive-Output", Robot::driveTrain->frontRightDrive->Get());
	//SmartDashboard::PutNumber("RL-Drive-Output", Robot::driveTrain->rearLeftDrive->Get());
	//SmartDashboard::PutNumber("RR-Drive-Output", Robot::driveTrain->rearRightDrive->Get());

	//SmartDashboard::PutNumber("FL-Pos-Voltage", Robot::driveTrain->frontLeftPos->GetVoltage());
	//SmartDashboard::PutNumber("FR-Pos-Voltage", Robot::driveTrain->frontRightPos->GetVoltage());
	//SmartDashboard::PutNumber("RL-Pos-Voltage", Robot::driveTrain->rearLeftPos->GetVoltage());
	//SmartDashboard::PutNumber("RR-Pos-Voltage", Robot::driveTrain->rearRightPos->GetVoltage());

	//SmartDashboard::PutNumber("FL-Pos-Turns", Robot::driveTrain->frontLeftPos->getturns());
	//SmartDashboard::PutNumber("FR-Pos-Turns", Robot::driveTrain->frontRightPos->getturns());
	//SmartDashboard::PutNumber("RL-Pos-Turns", Robot::driveTrain->rearLeftPos->getturns());
	//SmartDashboard::PutNumber("RR-Pos-Turns", Robot::driveTrain->rearRightPos->getturns());

	//SmartDashboard::PutData("FL-PID", Robot::driveTrain->frontLeft);
	//SmartDashboard::PutData("FR-PID", Robot::driveTrain->frontRight);
	//SmartDashboard::PutData("RL-PID", Robot::driveTrain->rearLeft);
	//SmartDashboard::PutData("RR-PID", Robot::driveTrain->rearRight);

	//SmartDashboard::PutNumber("FL-PID-Error", Robot::driveTrain->frontLeft->GetError());
	//SmartDashboard::PutNumber("FR-PID-Error", Robot::driveTrain->frontRight->GetError());
	//SmartDashboard::PutNumber("RL-PID-Error", Robot::driveTrain->rearLeft->GetError());
	//SmartDashboard::PutNumber("RR-PID-Error", Robot::driveTrain->rearRight->GetError());

	//SmartDashboard::PutNumber("FL-PID-Output", Robot::driveTrain->frontLeft->Get());
	//SmartDashboard::PutNumber("FR-PID-Output", Robot::driveTrain->frontRight->Get());
	//SmartDashboard::PutNumber("RL-PID-Output", Robot::driveTrain->rearLeft->Get());
	//SmartDashboard::PutNumber("RR-PID-Output", Robot::driveTrain->rearRight->Get());

	//SmartDashboard::PutData("Tote1-PID", Robot::toteElevator1->DebugGetPIDController());

	//SmartDashboard::PutNumber("pdp Total Voltage", RobotMap::pdp->GetVoltage());
	//SmartDashboard::PutNumber("pdp current channel reading", RobotMap::pdp->GetCurrent(pdpCurrentChannel));
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool UpdateSmartDashboard::IsFinished() {
	return false;
}

// ==========================================================================
// Called once after IsFinished returns true

void UpdateSmartDashboard::End() {
	
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void UpdateSmartDashboard::Interrupted() {
}

// ==========================================================================

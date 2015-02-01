#include "UpdateSmartDashboard.h"
#include "../Robot.h"
#include <WPILib.h>

// ==========================================================================

UpdateSmartDashboard::UpdateSmartDashboard() {
	SetRunWhenDisabled(true);
}

// ==========================================================================
// Called just before this Command runs the first time

void UpdateSmartDashboard::Initialize() {
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void UpdateSmartDashboard::Execute() {
	SmartDashboard::PutNumber("FLoutputDrive", Robot::driveTrain->frontLeftDrive->Get());
	SmartDashboard::PutNumber("FRoutputDrive", Robot::driveTrain->frontRightDrive->Get());
	SmartDashboard::PutNumber("RLoutputDrive", Robot::driveTrain->rearLeftDrive->Get());
	SmartDashboard::PutNumber("RRoutputDrive", Robot::driveTrain->rearRightDrive->Get());
	SmartDashboard::PutNumber("FrontLeftVolt", Robot::driveTrain->frontLeftPos->GetVoltage());
	SmartDashboard::PutNumber("FrontRightVolt", Robot::driveTrain->frontRightPos->GetVoltage());
	SmartDashboard::PutNumber("RearLeftVolt", Robot::driveTrain->rearLeftPos->GetVoltage());
	SmartDashboard::PutNumber("RearRightVolt", Robot::driveTrain->rearRightPos->GetVoltage());
	SmartDashboard::PutNumber("FrontLeftturns", Robot::driveTrain->frontLeftPos->getturns());
	SmartDashboard::PutNumber("FrontRightturns", Robot::driveTrain->frontRightPos->getturns());
	SmartDashboard::PutNumber("RearLeftturns", Robot::driveTrain->rearLeftPos->getturns());
	SmartDashboard::PutNumber("RearRightturns", Robot::driveTrain->rearRightPos->getturns());

	SmartDashboard::PutNumber("StickX", Robot::oi->GetJoystickX());
	SmartDashboard::PutNumber("StickY", Robot::oi->GetJoystickY());
	SmartDashboard::PutNumber("StickZ", Robot::oi->GetJoystickZ());

	SmartDashboard::PutData("FLpid", Robot::driveTrain->frontLeft);
	SmartDashboard::PutNumber("FLError", Robot::driveTrain->frontLeft->GetError());
	SmartDashboard::PutNumber("FLoutput", Robot::driveTrain->frontLeft->Get());
	SmartDashboard::PutData("FRpid", Robot::driveTrain->frontRight);
	SmartDashboard::PutNumber("FRError", Robot::driveTrain->frontRight->GetError());
	SmartDashboard::PutNumber("FRoutput", Robot::driveTrain->frontRight->Get());
	SmartDashboard::PutData("RLpid", Robot::driveTrain->rearLeft);
	SmartDashboard::PutNumber("RLError", Robot::driveTrain->rearLeft->GetError());
	SmartDashboard::PutNumber("RLoutput", Robot::driveTrain->rearLeft->Get());
	SmartDashboard::PutData("RRpid", Robot::driveTrain->rearRight);
	SmartDashboard::PutNumber("RRError", Robot::driveTrain->rearRight->GetError());
	SmartDashboard::PutNumber("RRoutput", Robot::driveTrain->rearRight->Get());
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

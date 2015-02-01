// ==========================================================================
// RotateBy class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#include "RotateBy.h"
#include "../Robot.h"
#include <string>

// ==========================================================================

#define P 0.05
#define I (P/2.0)
#define D (P/8.0)
#define F 0.0

#define INPUT_MIN -180
#define INPUT_MAX  180

#define OUTPUT_MIN -1.0
#define OUTPUT_MAX  1.0

#define ABSOLUTE_TOLERANCE 3.0

#define TIMEOUT_SECONDS 2.0

// ==========================================================================

RotateBy::RotateBy(const char* name, double rotateByDegrees)
: Command(name), _pidCtrl(nullptr), _rotateByDegrees(rotateByDegrees) {
	std::cout << "RotateBy::RotateBy(\"" << name << "\", " << rotateByDegrees << ")" << std::endl;

	Requires(Robot::driveTrain);

	_pidCtrl = new PIDController(P, I, D, F, Robot::gyroSub, this);
	_pidCtrl->SetInputRange(INPUT_MIN, INPUT_MAX);
	_pidCtrl->SetOutputRange(OUTPUT_MIN, OUTPUT_MAX);
	_pidCtrl->SetContinuous(true);
	_pidCtrl->SetAbsoluteTolerance(ABSOLUTE_TOLERANCE); // degrees
	_pidCtrl->Disable();
}

// ==========================================================================
// Called just before this Command runs the first time

void RotateBy::Initialize() {
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(TIMEOUT_SECONDS);
	_pidCtrl->SetSetpoint(CalculateSetpoint());
	_pidCtrl->Enable();
}

// ==========================================================================
// Called repeatedly when this Command is scheduled to run

void RotateBy::Execute() {
}

// ==========================================================================
// Make this return true when this Command no longer needs to run Execute.

bool RotateBy::IsFinished() {
	if (IsTimedOut()) {
		std::cout << GetName() << "::IsFinished -> IsTimedOut" << std::endl;
		return true;
	}
	if (_pidCtrl->OnTarget()) {
		std::cout << GetName() << "::IsFinished -> OnTarget" << std::endl;
		return true;
	}
	return false;
}

// ==========================================================================
// Called once after IsFinished returns true

void RotateBy::End() {
	std::cout << GetName() << "::End" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void RotateBy::Interrupted() {
	std::cout << GetName() << "::Interrupted" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void RotateBy::PIDWrite(float output) {
	std::cout << GetName() << ": PIDWrite(" << output << ")" << std::endl;
	Robot::driveTrain->Crab(output, 0.0, 0.0);
}

// ==========================================================================

double RotateBy::CalculateSetpoint() const {
	auto angle = GetCurrentPosition() + _rotateByDegrees;
	if (angle < INPUT_MIN) {
		angle += (INPUT_MAX - INPUT_MIN);
	}
	else if (angle > INPUT_MAX) {
		angle -= (INPUT_MAX - INPUT_MIN);
	}
	return angle;
}

// ==========================================================================

double RotateBy::GetCurrentPosition() const {
	return Robot::gyroSub->PIDGet();
}

// ==========================================================================

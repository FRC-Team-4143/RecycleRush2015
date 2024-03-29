// ==========================================================================
// RotateBy class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#include "RotateBy.h"
#include "../Logger.h"
#include "../Robot.h"
#include <string>
#include <sstream>

// ==========================================================================

#if 1
	#define P 0.05
	#define I (P/2.0)
	#define D (P/8.0)
	#define F 0.0

	#define INPUT_MIN -180
	#define INPUT_MAX  180

	#define OUTPUT_MIN -0.75
	#define OUTPUT_MAX  0.75
#else
	#define P 0.1
	#define I 0
	#define D 0
	#define F 0.0

	#define INPUT_MIN 0
	#define INPUT_MAX 360

	#define OUTPUT_MIN -0.5
	#define OUTPUT_MAX  0.5
#endif

#define ABSOLUTE_TOLERANCE 2.0

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
}

// ==========================================================================
// Called just before this Command runs the first time

void RotateBy::Initialize() {
	LOG(GetName().append("::Initialize"));
	SetTimeout(TIMEOUT_SECONDS);
	auto setpoint = CalculateSetpoint();
	std::cout << "Setpoint: " << setpoint << std::endl;
	_pidCtrl->SetSetpoint(setpoint);
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
		LOG(GetName().append("::IsFinished -> IsTimedOut"));
		std::cout << "Current Position: " << GetCurrentPosition() << std::endl;
		return true;
	}
	if (_pidCtrl->OnTarget()) {
		LOG(GetName().append("::IsFinished -> OnTarget"));
		std::cout << "Current Position: " << GetCurrentPosition() << std::endl;
		return true;
	}
	return false;
}

// ==========================================================================
// Called once after IsFinished returns true

void RotateBy::End() {
	LOG(GetName().append("::End"));
	_pidCtrl->Disable();
}

// ==========================================================================
// Called when another command which requires this subsystem is scheduled to run

void RotateBy::Interrupted() {
	LOG(GetName().append("::Interrupted"));
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void RotateBy::PIDWrite(float output) {
	std::ostringstream ss;
	ss << GetName() << ": PIDWrite(" << output << ")";
	LOG(ss.str());
	Robot::driveTrain->Crab(output, 0.0, 0.0, false);
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

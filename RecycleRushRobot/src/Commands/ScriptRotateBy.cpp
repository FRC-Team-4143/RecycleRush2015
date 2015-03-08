#include "ScriptRotateBy.h"
#include "../Robot.h"
#include <iostream>

// ==========================================================================

#define P 0.05
#define I (P/2.0)
#define D (P/8.0)
#define F 0.0

#define INPUT_MIN -180
#define INPUT_MAX  180

#define OUTPUT_MIN -0.75
#define OUTPUT_MAX  0.75

#define ABSOLUTE_TOLERANCE 2.0

// ==========================================================================

ScriptRotateBy::ScriptRotateBy(const char* name, float rotateByDegrees, float timeoutSeconds)
: Command(name), _rotateByDegrees(rotateByDegrees), _timeoutSeconds(timeoutSeconds)
{
	std::cout << GetName() << "::ctor(" << rotateByDegrees << ", " << timeoutSeconds << ")" << std::endl;
	Requires(Robot::driveTrain);
	Requires(Robot::gyroSub);

	_pidCtrl = new PIDController(P, I, D, F, Robot::gyroSub, this);
	_pidCtrl->SetInputRange(INPUT_MIN, INPUT_MAX);
	_pidCtrl->SetOutputRange(OUTPUT_MIN, OUTPUT_MAX);
	_pidCtrl->SetContinuous(true);
	_pidCtrl->SetAbsoluteTolerance(ABSOLUTE_TOLERANCE); // degrees
}

// ==========================================================================

void ScriptRotateBy::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_timeoutSeconds);
	auto setpoint = CalculateSetpoint();
	std::cout << "Setpoint: " << setpoint << std::endl;
	_pidCtrl->SetSetpoint(setpoint);
	_pidCtrl->Enable();
}

// ==========================================================================

void ScriptRotateBy::Execute()
{
}

// ==========================================================================

bool ScriptRotateBy::IsFinished()
{
	if (IsTimedOut()) {
		std::cout << GetName() << "::IsFinished -> IsTimedOut" << std::endl;
		std::cout << GetName() << "::IsFinished -> Current Position: " << GetCurrentPosition() << std::endl;
		return true;
	}
	if (_pidCtrl->OnTarget()) {
		std::cout << GetName() << "::IsFinished -> OnTarget" << std::endl;
		std::cout << GetName() << "::IsFinished -> CurrentPosition: " << GetCurrentPosition() << std::endl;
		return true;
	}
	return false;
}

// ==========================================================================

void ScriptRotateBy::End()
{
	std::cout << GetName() << "::End" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================

void ScriptRotateBy::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void ScriptRotateBy::PIDWrite(float output) {
	std::cout << GetName() << "::PIDWrite(" << output << ")" << std::endl;
	Robot::driveTrain->Crab(output, 0.0, 0.0);
}

// ==========================================================================
// Internal methods
// ==========================================================================

float ScriptRotateBy::CalculateSetpoint() const {
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

float ScriptRotateBy::GetCurrentPosition() const {
	return Robot::gyroSub->PIDGet();
}

// ==========================================================================

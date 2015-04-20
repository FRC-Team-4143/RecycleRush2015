#include "ScriptRotateByX.h"
#include "../Robot.h"
#include <iostream>

// ==========================================================================

#define P 0.02
#define I (P/2.0)
#define D (P/8.0)
#define F 0.0

#define INPUT_MIN -180
#define INPUT_MAX  180

#define OUTPUT_MIN -0.75
#define OUTPUT_MAX  0.75

#define ABSOLUTE_TOLERANCE 1.0

// ==========================================================================

ScriptRotateByX::ScriptRotateByX(const char* name, float rotateByDegrees, float timeoutSeconds, int stableTicksThreshold, float maxSpeed, float p)
: Command(name), _rotateByDegrees(rotateByDegrees), _timeoutSeconds(timeoutSeconds), _stableTicksThreshold(stableTicksThreshold), _stableTicks(0)
{
	std::cout << GetName() << "::ctor(" << rotateByDegrees << ", " << timeoutSeconds << ")" << std::endl;
	Requires(Robot::driveTrain);
	Requires(Robot::gyroSub);

	p = p ? p : P;
	float i = p / 2.0;
	float d = p / 8.0;

	_pidCtrl = new PIDController(p, i, d, F, Robot::gyroSub, this);
	_pidCtrl->SetInputRange(INPUT_MIN, INPUT_MAX);
	_pidCtrl->SetOutputRange(maxSpeed > 0 ? -maxSpeed : OUTPUT_MIN, maxSpeed > 0 ? maxSpeed : OUTPUT_MAX);
	_pidCtrl->SetContinuous(true);
	_pidCtrl->SetAbsoluteTolerance(ABSOLUTE_TOLERANCE); // degrees
}

// ==========================================================================

ScriptRotateByX::~ScriptRotateByX() {
	if (_pidCtrl != nullptr) {
		if (_pidCtrl->IsEnabled()) {
			_pidCtrl->Disable();
		}
		delete _pidCtrl;
		_pidCtrl = nullptr;
	}
}

// ==========================================================================

void ScriptRotateByX::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_timeoutSeconds);
	auto setpoint = CalculateSetpoint();
	std::cout << "Setpoint: " << setpoint << std::endl;
	_pidCtrl->SetSetpoint(setpoint);
	_pidCtrl->Enable();
}

// ==========================================================================

void ScriptRotateByX::Execute()
{
}

// ==========================================================================

bool ScriptRotateByX::IsFinished()
{
	if (IsTimedOut()) {
		std::cout << GetName() << "::IsFinished -> IsTimedOut" << std::endl;
		std::cout << GetName() << "::IsFinished -> Current Position: " << GetCurrentPosition() << std::endl;
		return true;
	}
	if (_pidCtrl->OnTarget()) {
		++_stableTicks;
		if (_stableTicks >= _stableTicksThreshold) {
			std::cout << GetName() << "::IsFinished -> OnTarget" << std::endl;
			std::cout << GetName() << "::IsFinished -> CurrentPosition: " << GetCurrentPosition() << std::endl;
			return true;
		}
	}
	else {
		_stableTicks = 0;
	}
	return false;
}

// ==========================================================================

void ScriptRotateByX::End()
{
	std::cout << GetName() << "::End" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================

void ScriptRotateByX::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void ScriptRotateByX::PIDWrite(float output) {
	std::cout << GetName() << "::PIDWrite(" << output << ")" << std::endl;
	Robot::driveTrain->Crab(output, 0.0, 0.0, false);
}

// ==========================================================================
// Internal methods
// ==========================================================================

float ScriptRotateByX::CalculateSetpoint() const {
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

float ScriptRotateByX::GetCurrentPosition() const {
	return Robot::gyroSub->PIDGet();
}

// ==========================================================================

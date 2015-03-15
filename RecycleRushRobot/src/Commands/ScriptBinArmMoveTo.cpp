#include "ScriptBinArmMoveTo.h"
#include "../Robot.h"
#include <iostream>

// ==========================================================================

#define P 0.07
#define I (P/2.0)
#define D (P/8.0)
#define F 0.0

// Specify arm position range in inches
#define INPUT_MIN 0
#define INPUT_MAX 84

// Specify arm motor control range (max range is -1 to 1)
#define OUTPUT_MIN -1.0
#define OUTPUT_MAX  1.0

// Specify absolute tolerance of arm position in inches
#define ABSOLUTE_TOLERANCE 0.1

// ==========================================================================

ScriptBinArmMoveTo::ScriptBinArmMoveTo(const char* name, float inches, float timeoutSeconds)
: Command(name), _inches(inches), _timeoutSeconds(timeoutSeconds)
{
	std::cout << GetName() << "::ctor(" << inches << ", " << timeoutSeconds << ")" << std::endl;
	Requires(Robot::binArm);

	_pidCtrl = new PIDController(P, I, D, F, this, this);
	_pidCtrl->SetInputRange(INPUT_MIN, INPUT_MAX);
	_pidCtrl->SetOutputRange(OUTPUT_MIN, OUTPUT_MAX);
	_pidCtrl->SetContinuous(false);
	_pidCtrl->SetAbsoluteTolerance(ABSOLUTE_TOLERANCE); // inches
}

// ==========================================================================

ScriptBinArmMoveTo::~ScriptBinArmMoveTo() {
	if (_pidCtrl != nullptr) {
		if (_pidCtrl->IsEnabled()) {
			_pidCtrl->Disable();
		}
		delete _pidCtrl;
		_pidCtrl = nullptr;
	}
}

// ==========================================================================

void ScriptBinArmMoveTo::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_timeoutSeconds);
	auto setpoint = CalculateSetpoint();
	std::cout << "Setpoint: " << setpoint << std::endl;
	_pidCtrl->SetSetpoint(setpoint);
	_pidCtrl->Enable();
}

// ==========================================================================

void ScriptBinArmMoveTo::Execute()
{
}

// ==========================================================================

bool ScriptBinArmMoveTo::IsFinished()
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

void ScriptBinArmMoveTo::End()
{
	std::cout << GetName() << "::End" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================

void ScriptBinArmMoveTo::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDSource methods
// ==========================================================================

double ScriptBinArmMoveTo::PIDGet() {
	return GetCurrentPosition();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void ScriptBinArmMoveTo::PIDWrite(float output) {
	std::cout << GetName() << "::PIDWrite(" << output << ")" << std::endl;
	Robot::binArm->Move(output);
}

// ==========================================================================
// Internal methods
// ==========================================================================

float ScriptBinArmMoveTo::CalculateSetpoint() const {
	auto inches = _inches;
	inches = std::max<float>(inches, INPUT_MIN);
	inches = std::min<float>(inches, INPUT_MAX);
	return inches;
}

// ==========================================================================

float ScriptBinArmMoveTo::GetCurrentPosition() const {
	return Robot::binArm->GetPositionInches();
}

// ==========================================================================

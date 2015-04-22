#include "ScriptBinArmMoveRel.h"
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

ScriptBinArmMoveRel::ScriptBinArmMoveRel(const char* name, float relInches, float timeoutSeconds, float maxSpeed)
: Command(name), _relInches(relInches), _timeoutSeconds(timeoutSeconds)
{
	std::cout << GetName() << "::ctor(" << relInches << ", " << timeoutSeconds << ")" << std::endl;
	Requires(Robot::binArm);

	_pidCtrl = new PIDController(P, I, D, F, this, this);
	//_pidCtrl->SetInputRange(INPUT_MIN, INPUT_MAX);
	_pidCtrl->SetOutputRange(maxSpeed > 0 ? -maxSpeed : OUTPUT_MIN, maxSpeed > 0 ? maxSpeed : OUTPUT_MAX);
	_pidCtrl->SetContinuous(false);
	_pidCtrl->SetAbsoluteTolerance(ABSOLUTE_TOLERANCE); // inches
}

// ==========================================================================

ScriptBinArmMoveRel::~ScriptBinArmMoveRel() {
	if (_pidCtrl != nullptr) {
		if (_pidCtrl->IsEnabled()) {
			_pidCtrl->Disable();
		}
		delete _pidCtrl;
		_pidCtrl = nullptr;
	}
}

// ==========================================================================

void ScriptBinArmMoveRel::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_timeoutSeconds);
	auto setpoint = CalculateSetpoint();
	std::cout << "Setpoint: " << setpoint << std::endl;
	_pidCtrl->SetSetpoint(setpoint);
	_pidCtrl->Enable();
}

// ==========================================================================

void ScriptBinArmMoveRel::Execute()
{
}

// ==========================================================================

bool ScriptBinArmMoveRel::IsFinished()
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

void ScriptBinArmMoveRel::End()
{
	std::cout << GetName() << "::End" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================

void ScriptBinArmMoveRel::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	_pidCtrl->Disable();
}

// ==========================================================================
// PIDSource methods
// ==========================================================================

double ScriptBinArmMoveRel::PIDGet() {
	return GetCurrentPosition();
}

// ==========================================================================
// PIDOutput methods
// ==========================================================================

void ScriptBinArmMoveRel::PIDWrite(float output) {
	std::cout << GetName() << "::PIDWrite(" << output << ")" << std::endl;
	Robot::binArm->Move(output);
}

// ==========================================================================
// Internal methods
// ==========================================================================

float ScriptBinArmMoveRel::CalculateSetpoint() const {
	auto inches = GetCurrentPosition() + _relInches;
	//inches = std::max<float>(inches, INPUT_MIN);
	//inches = std::min<float>(inches, INPUT_MAX);
	return inches;
}

// ==========================================================================

float ScriptBinArmMoveRel::GetCurrentPosition() const {
	return Robot::binArm->GetPositionInches();
}

// ==========================================================================

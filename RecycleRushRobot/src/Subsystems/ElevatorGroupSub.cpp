#include "ElevatorGroupSub.h"
#include "../Logger.h"
#include "../Commands/ToteElevatorGroupMove.h"

// ==========================================================================

ElevatorGroupSub::ElevatorGroupSub()
: Subsystem("ElevatorGroup"), _elevators() {
	std::cout << GetName() << "::ctor" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorGroupSub::InitDefaultCommand() {
	std::cout << GetName() << "::InitDefaultCommand" << std::endl;

	SetDefaultCommand(new ToteElevatorGroupMove());
}

// ==========================================================================
// Methods for configuring the elevator group
// ==========================================================================

void ElevatorGroupSub::AddElevator(ElevatorSub* elevator) {
	_elevators.push_back(elevator);
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

void ElevatorGroupSub::MoveDown(double inches) {
	for (auto iter = _elevators.begin(); iter != _elevators.end(); iter++) {
		(*iter)->MoveDown(inches);
	}
}

void ElevatorGroupSub::MoveUp(double inches) {
	for (auto iter = _elevators.begin(); iter != _elevators.end(); iter++) {
		(*iter)->MoveUp(inches);
	}
}

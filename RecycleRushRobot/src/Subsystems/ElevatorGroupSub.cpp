#include "ElevatorGroupSub.h"
#include "../Logger.h"

// ==========================================================================

ElevatorGroupSub::ElevatorGroupSub()
: Subsystem("ElevatorGroup"), _elevators() {
	std::cout << GetName() << "::ctor" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorGroupSub::InitDefaultCommand() {
	LOG("ElevatorGroupSub::InitDefaultCommand");
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MyCommand());
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
	// TODO
}

void ElevatorGroupSub::MoveUp(double inches) {
	// TODO
}

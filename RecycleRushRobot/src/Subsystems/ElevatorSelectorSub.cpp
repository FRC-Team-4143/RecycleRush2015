#include "ElevatorSelectorSub.h"
#include "../Logger.h"

// ==========================================================================

ElevatorSelectorSub::ElevatorSelectorSub()
: Subsystem("ElevatorSelector"),
  _elevators(), _selectedIndex(-1) {
	std::cout << GetName() << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorSelectorSub::InitDefaultCommand() {
	LOG("ElevatorSelectorSub::InitDefaultCommand");
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MyCommand());
}

// ==========================================================================
// Methods for configuring the elevator selector
// ==========================================================================

void ElevatorSelectorSub::AddElevator(ElevatorSub* elevator) {
	_elevators.push_back(elevator);
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

// TODO

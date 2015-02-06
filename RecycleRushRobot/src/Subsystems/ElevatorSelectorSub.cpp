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

ElevatorSub* ElevatorSelectorSub::SelectTop() {
	_selectedIndex = NumElevators() - 1;
	return Selected();
}

ElevatorSub* ElevatorSelectorSub::SelectBottom() {
	if (NumElevators() > 0) {
		_selectedIndex = 0;
	}
	return Selected();
}

ElevatorSub* ElevatorSelectorSub::SelectNextUpper() {
	if (_selectedIndex < (NumElevators() - 1)) {
		_selectedIndex++;
	}
	return Selected();
}

ElevatorSub* ElevatorSelectorSub::SelectNextLower() {
	if (_selectedIndex > 0) {
		_selectedIndex--;
	}
	return Selected();
}

ElevatorSub* ElevatorSelectorSub::SelectIndex(int index) {
	if (index >= 0 && index < NumElevators()) {
		_selectedIndex = index;
	}
	return Selected();
}

ElevatorSub* ElevatorSelectorSub::Selected() const {
	if (_selectedIndex >= 0 && _selectedIndex < NumElevators()) {
		return _elevators[_selectedIndex];
	}
	return nullptr;
}

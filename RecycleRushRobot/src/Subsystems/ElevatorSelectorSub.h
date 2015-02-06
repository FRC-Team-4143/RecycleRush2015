#ifndef ELEVATORSELECTORSUB_H
#define ELEVATORSELECTORSUB_H

#include <WPILib.h>
#include "ElevatorSub.h"

//
// The ElevatorSelectorSub subsystem manages the selection of an active elevator.
//
// @author FRC 4143
//
class ElevatorSelectorSub: public Subsystem {
public:
	ElevatorSelectorSub();

	// Subsystem methods
	virtual void InitDefaultCommand();

	void AddElevator(ElevatorSub* elevator); // Add them bottom to top

	ElevatorSub* SelectTop();
	ElevatorSub* SelectBottom();
	ElevatorSub* SelectNextUpper();
	ElevatorSub* SelectNextLower();
	ElevatorSub* SelectIndex(int index);
	ElevatorSub* Selected() const;

protected:
	int NumElevators() const { return _elevators.size(); }

private:
	std::vector<ElevatorSub*> _elevators;
	int _selectedIndex;
};

#endif

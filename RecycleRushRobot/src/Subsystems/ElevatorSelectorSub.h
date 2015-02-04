#ifndef ELEVATORSELECTORSUB_H
#define ELEVATORSELECTORSUB_H

#include <WPILib.h>
#include "ElevatorSub.h"

//
// The ElevatorSelectorSub subsystem manages the selection of an active elevator.
//
// @author JKSalmon
//
class ElevatorSelectorSub: public Subsystem {
public:
	ElevatorSelectorSub();

	// Subsystem methods
	virtual void InitDefaultCommand();

	void AddElevator(ElevatorSub* elevator); // Add them bottom to top

	void SelectTop();
	void SelectBottom();
	void SelectNextUpper();
	void SelectNextLower();
	void SelectIndex(int index);

	ElevatorSub* Selected() const;

private:
	std::vector<ElevatorSub*> _elevators;
	int _selectedIndex;
};

#endif

#ifndef ELEVATORGROUPSUB_H
#define ELEVATORGROUPSUB_H

#include <WPILib.h>
#include "ElevatorSub.h"

//
// The ElevatorGroupSub subsystem manages a set of elevators that move as a unit.
//
// @author FRC 4143
//
class ElevatorGroupSub: public Subsystem {
public:
	ElevatorGroupSub();

	// Subsystem methods
	virtual void InitDefaultCommand();

	void AddElevator(ElevatorSub* elevator); // Add elevators bottom to top? Don't think it matters at this time.

	void MoveDown(double inches);
	void MoveUp(double inches);

protected:
	int NumElevators() const { return _elevators.size(); }

private:
	std::vector<ElevatorSub*> _elevators;
};

#endif

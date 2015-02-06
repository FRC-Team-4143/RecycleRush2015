#ifndef ELEVATORSUB_H
#define ELEVATORSUB_H

#include <WPILib.h>
#include <Commands/PIDSubsystem.h>
#include "Modules/PIDParameters.h"

//
// The ElevatorSub subsystem represents an elevator for picking up totes or
// bins. Other elevators may exist above or below it on the same housing.
//
// @author JKSalmon
//
class ElevatorSub: public PIDSubsystem {
public:
	ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams);

	// Subsystem methods
	virtual void InitDefaultCommand();

	// PIDSubsystem methods
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);

	void SetPositions(double bottomPosition, double loadPosition, double topPosition, double upDownDelta, double neighborGapDelta);
	void SetLowerNeighbor(ElevatorSub* lowerNeighbor) { _lowerNeighbor = lowerNeighbor; }
	void SetUpperNeighbor(ElevatorSub* upperNeighbor) { _upperNeighbor = upperNeighbor; }

	double GetPosition();
	void GoDown();
	void GoUp();
	void GoToBottom();
	void GoToLoad();
	void GoToTop();
	void GoToPosition(double position);

private:
	SpeedController* myMotor() { return _motor; }
	Encoder* myEncoder() { return _encoder; }
	ElevatorSub* myLowerNeighbor() { return _lowerNeighbor; }
	ElevatorSub* myUpperNeighbor() { return _upperNeighbor; }

	SpeedController* _motor;
	Encoder* _encoder;
	ElevatorSub* _lowerNeighbor;
	ElevatorSub* _upperNeighbor;

	double _bottomPosition;
	double _loadPosition;
	double _topPosition;
	double _upDownDelta;
	double _neighborGapDelta;
};

#endif

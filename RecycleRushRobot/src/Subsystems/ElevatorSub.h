#ifndef ELEVATORSUB_H
#define ELEVATORSUB_H

#include <WPILib.h>
#include <Commands/PIDSubsystem.h>
#include "Modules/PIDParameters.h"

//
// The ElevatorSub subsystem represents an elevator for picking up totes or
// bins. Other elevators may exist above or below it on the same housing.
//
// @author FRC 4143
//
class ElevatorSub: public PIDSubsystem {
public:
	ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams);

	// Subsystem methods
	virtual void InitDefaultCommand();

	// PIDSubsystem methods
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);

	void SetDimensions(int countsPerRotation, double inchesPerRotation);
	void SetPositions(double bottomPosition, double loadPosition, double topPosition, double upDownDelta, double lowerMargin, double upperMargin);
	void SetLowerNeighbor(ElevatorSub* lowerNeighbor) { _lowerNeighbor = lowerNeighbor; }
	void SetUpperNeighbor(ElevatorSub* upperNeighbor) { _upperNeighbor = upperNeighbor; }

	void GoDown();
	void GoUp();
	void GoToBottom();
	void GoToLoad();
	void GoToTop();
	void GoToPosition(double position);
	void HoldPosition();

private:
	SpeedController* myMotor() { return _motor; }
	Encoder* myEncoder() { return _encoder; }
	ElevatorSub* myLowerNeighbor() { return _lowerNeighbor; }
	ElevatorSub* myUpperNeighbor() { return _upperNeighbor; }

	SpeedController* _motor;
	Encoder* _encoder;
	ElevatorSub* _lowerNeighbor;
	ElevatorSub* _upperNeighbor;

	int _countsPerRotation;
	double _inchesPerRotation;
	double _bottomPosition;
	double _loadPosition;
	double _topPosition;
	double _upDownDelta;
	double _lowerMargin;
	double _upperMargin;
};

#endif

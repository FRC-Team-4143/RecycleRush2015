#ifndef ELEVATORSUB_H
#define ELEVATORSUB_H

#include <WPILib.h>
#include <Commands/PIDSubsystem.h>
#include "Modules/ICommandFactory.h"
#include "Modules/PIDParameters.h"

//
// The ElevatorSub subsystem represents an elevator for picking up totes or
// bins. Other elevators may exist above or below it on the same housing.
//
// @author FRC 4143
//
class ElevatorSub: public PIDSubsystem {
public:
	ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams, ICommandFactory* defaultCommandFactory = nullptr);

	// Subsystem methods
	virtual void InitDefaultCommand();

	// PIDSubsystem methods
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);

	void SetEncoderDimensions(int countsPerRotation, double inchesPerRotation);
	void SetPositions(double bottomInches, double loadInches, double topInches, double deltaInches, double lowerMarginInches, double upperMarginInches);
	void SetLowerNeighbor(ElevatorSub* lowerNeighbor) { _lowerNeighbor = lowerNeighbor; }
	void SetUpperNeighbor(ElevatorSub* upperNeighbor) { _upperNeighbor = upperNeighbor; }

	void GoDown();
	void GoUp();
	void GoToBottom();
	void GoToLoad();
	void GoToTop();
	void GoToHeight(double inches);
	void HoldPosition();

	void MoveDown(double inches);
	void MoveUp(double inches);

protected:
	SpeedController* myMotor() { return _motor; }
	Encoder* myEncoder() { return _encoder; }
	ElevatorSub* myLowerNeighbor() { return _lowerNeighbor; }
	ElevatorSub* myUpperNeighbor() { return _upperNeighbor; }

	void GoToPosition(double position);
	double CountToInches(double count) const;
	double InchesToCount(double inches) const;

private:
	ICommandFactory* _defaultCommandFactory;
	SpeedController* _motor;
	Encoder* _encoder;
	ElevatorSub* _lowerNeighbor;
	ElevatorSub* _upperNeighbor;

	int _countsPerRotation;
	double _inchesPerRotation;
	double _bottomInches;
	double _loadInches;
	double _topInches;
	double _deltaInches;
	double _lowerMarginInches;
	double _upperMarginInches;
};

#endif

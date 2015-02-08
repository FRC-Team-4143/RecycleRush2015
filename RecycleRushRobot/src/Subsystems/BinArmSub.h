#ifndef BINARMSUB_H
#define BINARMSUB_H

#include <WPILib.h>
#include <Commands/PIDSubsystem.h>
#include "Modules/PIDParameters.h"

//
// The BinArmSub subsystem represents an arm that moves the bin hook in and out.
//
// @author FRC 4143
//
class BinArmSub: public PIDSubsystem {
public:
	BinArmSub(SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams);

	// Subsystem methods
	virtual void InitDefaultCommand();

	// PIDSubsystem methods
	virtual double ReturnPIDInput();
	virtual void UsePIDOutput(double output);

	void SetEncoderDimensions(int countsPerRotation, double inchesPerRotation);
	void SetArmDimensions(double minInches, double startupInches, double maxInches);

	void FullyRetract();
	void FullyExtend();
	void MoveRel(double inches);
	void MoveTo(double inches);

protected:
	SpeedController* myMotor() { return _motor; }
	Encoder* myEncoder() { return _encoder; }

	void GoToPosition(double position);
	double CountToInches(double count) const;
	double InchesToCount(double inches) const;
	double MinCount() const;
	double MaxCount() const;

private:
	SpeedController* _motor;
	Encoder* _encoder;

	int _countsPerRotation;
	double _inchesPerRotation;
	double _minInches;
	double _startupInches;
	double _maxInches;
};

#endif

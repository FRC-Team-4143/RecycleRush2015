#ifndef BINARMSUB_H
#define BINARMSUB_H

#include <WPILib.h>
#include <Commands/Subsystem.h>

//
// The BinArmSub subsystem represents an arm that moves the bin hook in and out.
//
class BinArmSub: public Subsystem {
public:
	BinArmSub(SpeedController* motor, Encoder* encoder);

	// Subsystem methods
	virtual void InitDefaultCommand();

	void SetArmDimensions(double minInches, double startInches, double maxInches);
	void SetEncoderDimensions(int countsPerRotation, double inchesPerRotation);

	double GetPositionInches() const;
	void Move(double speed);
	void ResetEncoder();
	void Stop();

protected:
	SpeedController* myMotor() const { return _motor; }
	Encoder* myEncoder() const { return _encoder; }

	double CountToInches(double count) const;
	double InchesToCount(double inches) const;
	double GetPositionCount() const;
	double MinCount() const;
	double MaxCount() const;
	double MinInches() const { return _minInches; }
	double MaxInches() const { return _maxInches; }
	double StartInches() const { return _startInches; }

private:
	SpeedController* _motor;
	Encoder* _encoder;

	int _countsPerRotation;
	double _inchesPerRotation;
	double _minInches;
	double _startInches;
	double _maxInches;
};

#endif

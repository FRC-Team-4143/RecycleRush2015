#include "BinArmSub.h"
#include "../Logger.h"
#include "../Commands/BinArmMove.h"

// ==========================================================================

BinArmSub::BinArmSub(SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams)
: PIDSubsystem("BinArm", pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _motor(motor), _encoder(encoder),
  _countsPerRotation(0), _inchesPerRotation(0),
  _minInches(0), _maxInches(0)
{
	std::cout << GetName() << "::ctor" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void BinArmSub::InitDefaultCommand() {
	std::cout << GetName() << "::InitDefaultCommand" << std::endl;

	SetDefaultCommand(new BinArmMove());
}

// ==========================================================================
// PIDSubsystem methods
// ==========================================================================

double BinArmSub::ReturnPIDInput() {
	return myEncoder()->PIDGet();
}

// ==========================================================================

void BinArmSub::UsePIDOutput(double output) {
	myMotor()->Set(output);
}

// ==========================================================================
// Methods for configuring the elevator
// ==========================================================================

void BinArmSub::SetEncoderDimensions(int countsPerRotation, double inchesPerRotation) {
	_countsPerRotation = countsPerRotation;
	_inchesPerRotation = inchesPerRotation;
}

void BinArmSub::SetPositions(double minInches, double maxInches) {
	_minInches = minInches;
	_maxInches = maxInches;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

void BinArmSub::FullyRetract() {
	MoveTo(_minInches);
}

void BinArmSub::FullyExtend() {
	MoveTo(_maxInches);
}

void BinArmSub::MoveTo(double inches) {
	GoToPosition(InchesToCount(inches));
}

// ==========================================================================
// Internal methods
// ==========================================================================

void BinArmSub::GoToPosition(double position) {
	if (position < InchesToCount(_minInches)) {
		position = InchesToCount(_minInches);
	}
	else if (position > InchesToCount(_maxInches)) {
		position = InchesToCount(_maxInches);
	}
	SetSetpoint(position);
}

double BinArmSub::CountToInches(double count) const {
	return count / _countsPerRotation * _inchesPerRotation;
}

double BinArmSub::InchesToCount(double inches) const {
	return inches / _inchesPerRotation * _countsPerRotation;
}

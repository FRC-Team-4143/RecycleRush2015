#include "BinArmSub.h"
#include "../Logger.h"
#include "../Commands/BinArmMove.h"

// ==========================================================================

BinArmSub::BinArmSub(SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams)
: PIDSubsystem("BinArm", pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _motor(motor), _encoder(encoder),
  _countsPerRotation(0), _inchesPerRotation(0),
  _minInches(0), _startupInches(0), _maxInches(0)
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

void BinArmSub::SetArmDimensions(double minInches, double startupInches, double maxInches) {
	_minInches = minInches;
	_startupInches = startupInches;
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

void BinArmSub::MoveRel(double inches) {
	GoToPosition(GetSetpoint() + InchesToCount(inches));
}

void BinArmSub::MoveTo(double inches) {
	GoToPosition(MinCount() + InchesToCount(inches));
}

// ==========================================================================
// Internal methods
// ==========================================================================

void BinArmSub::GoToPosition(double position) {
	position = std::min(position, MinCount());
	position = std::max(position, MaxCount());
	SetSetpoint(position);
}

double BinArmSub::CountToInches(double count) const {
	return count / _countsPerRotation * _inchesPerRotation;
}

double BinArmSub::InchesToCount(double inches) const {
	return inches / _inchesPerRotation * _countsPerRotation;
}

double BinArmSub::MinCount() const {
	return -InchesToCount(_startupInches - _minInches);
}

double BinArmSub::MaxCount() const {
	return InchesToCount(_maxInches - _startupInches);
}

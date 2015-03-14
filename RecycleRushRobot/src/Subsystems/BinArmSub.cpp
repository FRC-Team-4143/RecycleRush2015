#include "BinArmSub.h"

// ==========================================================================

const int DEFAULT_COUNTS_PER_ROTATION = 120;
const int DEFAULT_INCHES_PER_ROTATION = 4;
const int DEFAULT_MIN_INCHES = 0;
const int DEFAULT_START_INCHES = 0;
const int DEFAULT_MAX_INCHES = 30;

// ==========================================================================

BinArmSub::BinArmSub(SpeedController* motor, Encoder* encoder)
: Subsystem("BinArm"),
  _motor(motor), _encoder(encoder),
  _countsPerRotation(DEFAULT_COUNTS_PER_ROTATION), _inchesPerRotation(DEFAULT_INCHES_PER_ROTATION),
  _minInches(DEFAULT_MIN_INCHES), _startInches(DEFAULT_START_INCHES), _maxInches(DEFAULT_MAX_INCHES)
{
	std::cout << GetName() << "::ctor" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void BinArmSub::InitDefaultCommand() {
	std::cout << GetName() << "::InitDefaultCommand" << std::endl;
	//SetDefaultCommand(new BinArmMove());
}

// ==========================================================================
// Methods for configuring the elevator
// ==========================================================================

void BinArmSub::SetArmDimensions(double minInches, double startInches, double maxInches) {
	_minInches = minInches;
	_startInches = startInches;
	_maxInches = maxInches;
}

void BinArmSub::SetEncoderDimensions(int countsPerRotation, double inchesPerRotation) {
	_countsPerRotation = countsPerRotation;
	_inchesPerRotation = inchesPerRotation;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

double BinArmSub::GetPositionInches() const {
	return MinInches() + CountToInches(GetPositionCount() - MinCount());
}

void BinArmSub::Move(double speed) {
	if (speed > 0) {
		if (GetPositionCount() >= MaxCount()) {
			speed = 0;
		}
	}
	else if (speed < 0) {
		if (GetPositionCount() <= MinCount()) {
			speed = 0;
		}
	}
	myMotor()->Set(speed);
}

void BinArmSub::ResetEncoder() {
	myEncoder()->Reset();
}

void BinArmSub::Stop() {
	myMotor()->Set(0);
}

// ==========================================================================
// Internal methods
// ==========================================================================

double BinArmSub::CountToInches(double count) const {
	return count / _countsPerRotation * _inchesPerRotation;
}

double BinArmSub::InchesToCount(double inches) const {
	return inches / _inchesPerRotation * _countsPerRotation;
}

double BinArmSub::GetPositionCount() const {
	return myEncoder()->Get();
}

double BinArmSub::MinCount() const {
	return -InchesToCount(StartInches() - MinInches());
}

double BinArmSub::MaxCount() const {
	return InchesToCount(MaxInches() - StartInches());
}

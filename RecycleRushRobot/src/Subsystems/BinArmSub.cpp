#include "BinArmSub.h"

// ==========================================================================

const int DEFAULT_COUNTS_PER_ROTATION = 120;
const double DEFAULT_INCHES_PER_ROTATION = 2.2;
const int DEFAULT_MIN_INCHES = 0;
const int DEFAULT_START_INCHES = 0;
const int DEFAULT_MAX_INCHES = 29;

// ==========================================================================

BinArmSub::BinArmSub(SpeedController* motor, Encoder* encoder, bool invertMotor)
: Subsystem("BinArm"),
  _motor(motor), _encoder(encoder),
  _countsPerRotation(DEFAULT_COUNTS_PER_ROTATION), _inchesPerRotation(DEFAULT_INCHES_PER_ROTATION),
  _minInches(DEFAULT_MIN_INCHES), _startInches(DEFAULT_START_INCHES), _maxInches(DEFAULT_MAX_INCHES),
  _invertMotor(invertMotor),
  _debug(false)
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

void BinArmSub::EnableDebug(bool debug) {
	_debug = debug;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

double BinArmSub::GetPositionInches() const {
	return MinInches() + CountToInches(GetPositionCount() - MinCount());
}

void BinArmSub::Move(double speed) {
	if (_debug) std::cout << "[DEBUG] " << GetName() << "::Move(" << speed << ")" << std::endl;
	if (_debug) DebugOutputState();
	if (speed > 0) {
		if (GetPositionCount() >= MaxCount()) {
			if (_debug) std::cout << "[DEBUG] " << GetName() << "::Move at max" << std::endl;
			speed = 0;
		}
	}
	else if (speed < 0) {
		if (GetPositionCount() <= MinCount()) {
			if (_debug) std::cout << "[DEBUG] " << GetName() << "::Move at min" << std::endl;
			speed = 0;
		}
	}
	myMotor()->Set(_invertMotor ? -speed : speed);
}

void BinArmSub::ResetEncoder() {
	myEncoder()->Reset();
}

void BinArmSub::Stop() {
	myMotor()->Set(0);
}

void BinArmSub::DebugOutputState() {
	std::cout << "[DEBUG] " << GetName() << " minCount=" << MinCount() << ", maxCount=" << MaxCount() << ", curr=" << GetPositionCount() << std::endl;
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

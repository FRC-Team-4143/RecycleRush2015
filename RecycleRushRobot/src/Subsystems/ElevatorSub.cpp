#include "ElevatorSub.h"
#include "../Logger.h"

// ==========================================================================

ElevatorSub::ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams)
: PIDSubsystem(name, pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _motor(motor), _encoder(encoder),
  _lowerNeighbor(nullptr), _upperNeighbor(nullptr),
  _countsPerRotation(0), _inchesPerRotation(0),
  _bottomPosition(0), _loadPosition(0), _topPosition(0), _upDownDelta(0), _lowerMargin(0), _upperMargin(0) {
	std::cout << "ElevatorSub::ElevatorSub(" << name << ")" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorSub::InitDefaultCommand() {
	LOG("ElevatorSub::InitDefaultCommand");
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MyCommand());
}

// ==========================================================================
// PIDSubsystem methods
// ==========================================================================

double ElevatorSub::ReturnPIDInput() {
	return myEncoder()->PIDGet();
}

// ==========================================================================

void ElevatorSub::UsePIDOutput(double output) {
	myMotor()->Set(output);
}

// ==========================================================================
// Methods for configuring the elevator
// ==========================================================================

void ElevatorSub::SetDimensions(int countsPerRotation, double inchesPerRotation) {
	_countsPerRotation = countsPerRotation;
	_inchesPerRotation = inchesPerRotation;
}

void ElevatorSub::SetPositions(double bottomPosition, double loadPosition, double topPosition, double upDownDelta, double lowerMargin, double upperMargin) {
	_bottomPosition = bottomPosition;
	_loadPosition   = loadPosition;
	_topPosition    = topPosition;
	_upDownDelta    = upDownDelta;
	_lowerMargin    = lowerMargin;
	_upperMargin    = upperMargin;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

void ElevatorSub::GoDown() {
	GoToPosition(GetPosition() - _upDownDelta);
}

void ElevatorSub::GoUp() {
	GoToPosition(GetPosition() + _upDownDelta);
}

void ElevatorSub::GoToBottom() {
	GoToPosition(_bottomPosition);
}

void ElevatorSub::GoToLoad() {
	GoToPosition(_loadPosition);
}

void ElevatorSub::GoToTop() {
	GoToPosition(_topPosition);
}

void ElevatorSub::GoToPosition(double position) {
	// TODO
}

void ElevatorSub::HoldPosition() {
	GoToPosition(GetPosition());
}

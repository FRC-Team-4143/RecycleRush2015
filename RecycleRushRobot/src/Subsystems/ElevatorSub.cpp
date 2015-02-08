#include "ElevatorSub.h"
#include "../Logger.h"

// ==========================================================================

ElevatorSub::ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams, ICommandFactory* defaultCommandFactory)
: PIDSubsystem(name, pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _defaultCommandFactory(defaultCommandFactory),
  _motor(motor), _encoder(encoder),
  _lowerNeighbor(nullptr), _upperNeighbor(nullptr),
  _countsPerRotation(16), _inchesPerRotation(4),
  _bottomInches(0), _loadInches(4), _topInches(50), _deltaInches(14), _lowerMarginInches(2), _upperMarginInches(2) {
	std::cout << "ElevatorSub::ElevatorSub(" << name << ")" << std::endl;
	SetOutputRange(-0.3, 0.3);

}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorSub::InitDefaultCommand() {
	std::cout << "Elevator(" << GetName() << ")::InitDefaultCommand" << std::endl;

	if (_defaultCommandFactory) {
		SetDefaultCommand(_defaultCommandFactory->CreateCommand());
	}
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

void ElevatorSub::SetEncoderDimensions(int countsPerRotation, double inchesPerRotation) {
	_countsPerRotation = countsPerRotation;
	_inchesPerRotation = inchesPerRotation;
}

void ElevatorSub::SetNeighbors(ElevatorSub* lowerNeighbor, ElevatorSub* upperNeighbor) {
	_lowerNeighbor = lowerNeighbor;
	_upperNeighbor = upperNeighbor;
}

void ElevatorSub::SetPositions(double bottomInches, double loadInches, double topInches, double deltaInches, double lowerMarginInches, double upperMarginInches) {
	_bottomInches      = bottomInches;
	_loadInches        = loadInches;
	_topInches         = topInches;
	_deltaInches       = deltaInches;
	_lowerMarginInches = lowerMarginInches;
	_upperMarginInches = upperMarginInches;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

void ElevatorSub::GoDown() {
	GoToPosition(GetPosition() - InchesToCount(_deltaInches));
}

void ElevatorSub::GoUp() {
	GoToPosition(GetPosition() + InchesToCount(_deltaInches));
}

void ElevatorSub::GoToBottom() {
	GoToHeight(_bottomInches);
}

void ElevatorSub::GoToLoad() {
	GoToHeight(_loadInches);
}

void ElevatorSub::GoToTop() {
	GoToHeight(_topInches);
}

void ElevatorSub::GoToHeight(double inches) {
	GoToPosition(InchesToCount(inches));
}

void ElevatorSub::HoldPosition() {
	GoToPosition(GetPosition());
}

void ElevatorSub::MoveDown(double inches) {
	// TODO
}

void ElevatorSub::MoveUp(double inches) {
	// TODO
}

// ==========================================================================
// Internal methods
// ==========================================================================

void ElevatorSub::GoToPosition(double position) {
	if (position < InchesToCount(_bottomInches)) {
		position = InchesToCount(_bottomInches);
	}
	else if (position > InchesToCount(_topInches)) {
		position = InchesToCount(_topInches);
	}
	// TODO - Add neighbor checking
	SetSetpoint(position);
}

double ElevatorSub::CountToInches(double count) const {
	return count / _countsPerRotation * _inchesPerRotation;
}

double ElevatorSub::InchesToCount(double inches) const {
	return inches / _inchesPerRotation * _countsPerRotation;
}

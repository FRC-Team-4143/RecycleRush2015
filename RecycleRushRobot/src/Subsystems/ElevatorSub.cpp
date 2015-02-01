#include "ElevatorSub.h"

// ==========================================================================

ElevatorSub::ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams, double unitDelta, double bottomPosition, double topPosition)
: PIDSubsystem(name, pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _motor(motor), _encoder(encoder),
  _lowerNeighbor(nullptr), _upperNeighbor(nullptr),
  _unitDelta(unitDelta), _bottomPosition(bottomPosition), _topPosition(topPosition) {
	std::cout << "ElevatorSub::ElevatorSub(" << name << ")" << std::endl;
}

// ==========================================================================
// Subsystem methods
// ==========================================================================

void ElevatorSub::InitDefaultCommand() {
	std::cout << "ElevatorSub::InitDefaultCommand" << std::endl;
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MyCommand());
}

// ==========================================================================
// PIDSubsystem methods
// ==========================================================================

double ElevatorSub::ReturnPIDInput() {
	// TODO
	return 0;
}

// ==========================================================================

void ElevatorSub::UsePIDOutput(double output) {
	// TODO
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

// TODO

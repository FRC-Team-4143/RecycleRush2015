#include "ElevatorSub.h"
#include "../Logger.h"

// ==========================================================================

ElevatorSub::ElevatorSub(const char* name, SpeedController* motor, Encoder* encoder, const PIDParameters& pidParams)
: PIDSubsystem(name, pidParams.P, pidParams.I, pidParams.D, pidParams.F),
  _motor(motor), _encoder(encoder),
  _lowerNeighbor(nullptr), _upperNeighbor(nullptr),
  _bottomPosition(0), _loadPosition(0), _deltaPosition(0), _topPosition(0) {
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

void ElevatorSub::SetPositions(double bottomPosition, double loadPosition, double deltaPosition, double topPosition) {
	_bottomPosition = bottomPosition;
	_loadPosition   = loadPosition;
	_deltaPosition  = deltaPosition;
	_topPosition    = topPosition;
}

// ==========================================================================
// Put methods for controlling this subsystem here.
// Call these from Commands.
// ==========================================================================

// TODO

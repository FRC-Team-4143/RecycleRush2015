#include "DoubleAutoMonitor.h"
#include <DriverStation.h>

DoubleAutoMonitor::DoubleAutoMonitor()
: _lastActiveMode(ActiveMode::None)
{
}

bool DoubleAutoMonitor::IsCompetition() {
	return DriverStation::GetInstance()->IsFMSAttached();
}

bool DoubleAutoMonitor::IsDoubleAutonomous() const {
	if (IsCompetition()) {
		if (ActiveMode::Autonomous == _lastActiveMode) {
			return true;
		}
	}
	return false;
}

void DoubleAutoMonitor::OnRobotInit() {
	_lastActiveMode = ActiveMode::None;
}

void DoubleAutoMonitor::OnAutonomousInit() {
	_lastActiveMode = ActiveMode::Autonomous;
}

void DoubleAutoMonitor::OnTeleopInit() {
	_lastActiveMode = ActiveMode::Teleop;
}

#include "ScriptDisplacementDrive.h"
#include "../Robot.h"
#include <iostream>

#define P			0.5
#define TOLERANCE   0.01

ScriptDisplacementDrive::ScriptDisplacementDrive(const char* name, double deltaX, double deltaY, double maxspeed, double timeoutSeconds)
: Command(name), _deltaX(deltaX), _deltaY(deltaY), _maxspeed(maxspeed), _timeoutSeconds(timeoutSeconds)
{
	std::cout << GetName() << "::ctor(" << deltaX << ", " << deltaY << ", " << maxspeed << ", " << timeoutSeconds << ")" << std::endl;
	Requires(Robot::driveTrain);
}

void ScriptDisplacementDrive::Initialize() {
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_timeoutSeconds);
	_angle = Robot::gyroSub->PIDGet();
	_angle /= 90.;
	_angle = floor(_angle + .5); // round
	_angle *= 90.;
	_startingX = Robot::gyroSub->GetDisplacementX();
	_startingY = Robot::gyroSub->GetDisplacementY();
	_targetX = _startingX + _deltaX;
	_targetY = _startingY + _deltaY;
}

void ScriptDisplacementDrive::Execute() {
	_currentX = Robot::gyroSub->GetDisplacementX();
	_currentY = Robot::gyroSub->GetDisplacementY();
	auto x = std::min(_maxspeed, std::max(-_maxspeed, (_targetX - _currentX) * P));
	auto y = std::min(_maxspeed, std::max(-_maxspeed, (_targetY - _currentY) * P));
	Robot::driveTrain->GyroCrab(_angle, x, y, false);
}

bool ScriptDisplacementDrive::IsFinished() {
	if (fabs(_targetX - _currentX) <= TOLERANCE && fabs(_targetY - _currentY) <= TOLERANCE)
		return true;
	return IsTimedOut();
}

void ScriptDisplacementDrive::End() {
	std::cout << GetName() << "::End" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0, false);
}

void ScriptDisplacementDrive::Interrupted() {
	std::cout << GetName() << "::Interrupted" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0, false);
}

#include "ScriptMouseDrive.h"
#include "../Robot.h"
#include <iostream>

#define P			.1
#define TOLERANCE   1.0

ScriptMouseDrive::ScriptMouseDrive(const char* name, double x, double y, double maxspeed, double seconds)
: Command(name), _x(x), _y(y), _maxspeed(maxspeed), _seconds(seconds)
{
	std::cout << GetName() << "::ctor(" << x << ", " << y << ", " << maxspeed << ", " << seconds << ")" << std::endl;
	Requires(Robot::driveTrain);
}

// Called just before this Command runs the first time
void ScriptMouseDrive::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_seconds);
	_angle = Robot::gyroSub->PIDGet();
	_angle /= 90.;
	_angle = floor(_angle + .5); // round
	_angle *= 90.;
	Robot::mouseSubsystem->GetPosition(_startingY, _startingX);
	_startingY *= -1.0;
	_x += _startingX;
	_y += _startingY;
}

// Called repeatedly when this Command is scheduled to run
void ScriptMouseDrive::Execute()
{
	Robot::mouseSubsystem->GetPosition(_currentY, _currentX);
	_currentY *= -1.0;
	Robot::driveTrain->GyroCrab(_angle,
			std::min(_maxspeed, std::max(-_maxspeed, (_currentX - _x) * P)),
			std::min(_maxspeed, std::max(-_maxspeed, (_currentY - _y) * P)));
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptMouseDrive::IsFinished()
{
	if (fabs(_currentX - _x) <= TOLERANCE && fabs(_currentY - _y) <= TOLERANCE)
		return true;
	return IsTimedOut();
}

// Called once after isFinished returns true
void ScriptMouseDrive::End()
{
	std::cout << GetName() << "::End" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptMouseDrive::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
	Robot::driveTrain->Crab(0, 0, 0);
}

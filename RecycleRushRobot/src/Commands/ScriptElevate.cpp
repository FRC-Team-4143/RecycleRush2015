#include "ScriptElevate.h"
#include "../Robot.h"
#include <iostream>

ScriptElevate::ScriptElevate(const char* name, float axis, float seconds)
: Command(name), _axis(axis), _seconds(seconds)
{
	std::cout << GetName() << "::ctor(" << axis << ", " << seconds << ")" << std::endl;
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void ScriptElevate::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_seconds);
}

// Called repeatedly when this Command is scheduled to run
void ScriptElevate::Execute()
{
	Robot::completeElevator->MoveElevator(_axis);
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptElevate::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void ScriptElevate::End()
{
	std::cout << GetName() << "::End" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptElevate::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
}

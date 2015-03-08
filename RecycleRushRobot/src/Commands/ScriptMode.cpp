#include "ScriptMode.h"
#include "../Robot.h"
#include <iostream>

ScriptMode::ScriptMode(const char* name, int mode)
: Command(name), _mode(mode)
{
	std::cout << GetName() << "::ctor()" << std::endl;
	Requires(Robot::completeElevator);
}

// Called just before this Command runs the first time
void ScriptMode::Initialize()
{
	std::cout << GetName() << "::Initialize" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void ScriptMode::Execute()
{
	Robot::completeElevator->SetMode(_mode);
}

// Make this return true when this Command no longer needs to run execute()
bool ScriptMode::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void ScriptMode::End()
{
	std::cout << GetName() << "::End" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ScriptMode::Interrupted()
{
	std::cout << GetName() << "::Interrupted" << std::endl;
}

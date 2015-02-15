#include "ClampClaw.h"
#include "../Robot.h"

ClampClaw::ClampClaw()
{
	Requires(Robot::pneumatics);
}

// Called just before this Command runs the first time
void ClampClaw::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ClampClaw::Execute()
{
	Robot::pneumatics->forward();
}

// Make this return true when this Command no longer needs to run execute()
bool ClampClaw::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ClampClaw::End()
{
	Robot::pneumatics->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClampClaw::Interrupted()
{
	Robot::pneumatics->stop();
}

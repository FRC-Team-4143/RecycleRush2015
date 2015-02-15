#include "ReleaseClaw.h"
#include "../Robot.h"

ReleaseClaw::ReleaseClaw()
{
	Requires(Robot::pneumatics);
}

// Called just before this Command runs the first time
void ReleaseClaw::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void ReleaseClaw::Execute()
{
	Robot::pneumatics->reverse();
}

// Make this return true when this Command no longer needs to run execute()
bool ReleaseClaw::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ReleaseClaw::End()
{
	Robot::pneumatics->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReleaseClaw::Interrupted()
{
	Robot::pneumatics->stop();
}

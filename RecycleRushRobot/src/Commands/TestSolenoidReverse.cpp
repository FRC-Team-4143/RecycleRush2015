#include "TestSolenoidReverse.h"
#include "../Robot.h"

TestSolenoidReverse::TestSolenoidReverse()
{
	Requires(Robot::pneumatics);
}

// Called just before this Command runs the first time
void TestSolenoidReverse::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TestSolenoidReverse::Execute()
{
	Robot::pneumatics->reverse();
}

// Make this return true when this Command no longer needs to run execute()
bool TestSolenoidReverse::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestSolenoidReverse::End()
{
	Robot::pneumatics->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestSolenoidReverse::Interrupted()
{
	Robot::pneumatics->stop();
}

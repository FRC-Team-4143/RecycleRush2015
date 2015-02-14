#include "TestSolenoidForward.h"
#include "../Robot.h"

TestSolenoidForward::TestSolenoidForward()
{
	Requires(Robot::pneumatics);
}

// Called just before this Command runs the first time
void TestSolenoidForward::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TestSolenoidForward::Execute()
{
	Robot::pneumatics->forward();
}

// Make this return true when this Command no longer needs to run execute()
bool TestSolenoidForward::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestSolenoidForward::End()
{
	Robot::pneumatics->stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestSolenoidForward::Interrupted()
{
	Robot::pneumatics->stop();
}

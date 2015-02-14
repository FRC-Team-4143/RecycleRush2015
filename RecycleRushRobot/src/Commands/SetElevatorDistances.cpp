#include "SetElevatorDistances.h"

SetElevatorDistances::SetElevatorDistances()
{
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void SetElevatorDistances::Initialize()
{
	printf("saveDistances started \n");
	Preferences* prefs = Preferences::GetInstance();
	printf("saveDistances prefs initialized \n");
	distance4_3 = SmartDashboard::GetNumber("Tote4-3 distance");
	distance3_2 = SmartDashboard::GetNumber("Tote3-2 distance");
	distance2_1 = SmartDashboard::GetNumber("Tote2-1 distance");
	printf("saveDistances numbers from smartdashboard \n");

	prefs->PutDouble("distance4_3", distance4_3);
	prefs->PutDouble("distance3_2", distance3_2);
	prefs->PutDouble("distance2_1", distance2_1);
	printf("saveDistances numbers set \n");

	prefs->Save();
	printf("saveDistances saved \n");

}

// Called repeatedly when this Command is scheduled to run
void SetElevatorDistances::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SetElevatorDistances::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SetElevatorDistances::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetElevatorDistances::Interrupted()
{

}

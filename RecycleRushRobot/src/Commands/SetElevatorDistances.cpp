#include "SetElevatorDistances.h"
#include "../Robot.h"

SetElevatorDistances::SetElevatorDistances()
{
	SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void SetElevatorDistances::Initialize()
{
	printf("saveDistances started \n");
	//initializes preferences
	Preferences* prefs = Preferences::GetInstance();
	printf("saveDistances prefs initialized \n");

	//takes distance values from smartdashboard
	distance4_3 = SmartDashboard::GetNumber("Tote4-3 distance");
	distance3_2 = SmartDashboard::GetNumber("Tote3-2 distance");
	distance2_1 = SmartDashboard::GetNumber("Tote2-1 distance");

	//sets the distances in the subsystem
	Robot::completeElevator->distance4_3 = distance4_3;
	Robot::completeElevator->distance3_2 = distance3_2;
	Robot::completeElevator->distance2_1 = distance2_1;

	//gets max values from smartdashboard
	tote4Max = SmartDashboard::GetNumber("Tote4-Max");
	tote3Max = SmartDashboard::GetNumber("Tote3-Max");
	tote2Max = SmartDashboard::GetNumber("Tote2-Max");
	tote1Max = SmartDashboard::GetNumber("Tote1-Max");

	printf("saveDistances numbers from smartdashboard \n");

	//sets distances in preferences
	prefs->PutDouble("distance4_3", distance4_3);
	prefs->PutDouble("distance3_2", distance3_2);
	prefs->PutDouble("distance2_1", distance2_1);

	//sets max values in preferences
	prefs->PutDouble("tote4-Max", tote4Max);
	prefs->PutDouble("tote3-Max", tote3Max);
	prefs->PutDouble("tote2-Max", tote2Max);
	prefs->PutDouble("tote1-Max", tote1Max);

	printf("saveDistances numbers set \n");

	//saves preferences
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

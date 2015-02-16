#include "CompleteElevator.h"
#include "../RobotMap.h"
#include "../Commands/CompleteElevatorDefaultCommand.h"

#define SPEED (float)5
#define COUNTS_PER_REV (float)120
#define INCHES_PER_REV (float)4
#define MAX (float)62  // inches
#define MIN (float)0

CompleteElevator::CompleteElevator() :
		Subsystem("CompleteElevator")
{
	toteElevator1PID       = RobotMap::toteElevator1PID;
	toteElevator2PID       = RobotMap::toteElevator2PID;
	toteElevator3PID       = RobotMap::toteElevator3PID;
	toteElevator4PID       = RobotMap::toteElevator4PID;
	armEncoder			   = RobotMap::binArmPos;
	prefs = Preferences::GetInstance();
	setpoint = 0;
}

void CompleteElevator::InitDefaultCommand()
{
	SetDefaultCommand(new CompleteElevatorDefaultCommand());
}

void CompleteElevator::MoveElevator(float trigger){
	//float setpoint1 = toteElevator1PID->GetSetpoint();
	//float setpoint2 = toteElevator2PID->GetSetpoint();
	//float setpoint3 = toteElevator3PID->GetSetpoint();
	//float setpoint4 = toteElevator4PID->GetSetpoint();

	setpoint = std::max((float)MIN, setpoint + (trigger*SPEED));

	armPos = armEncoder->GetDistance();

	distance4_3 = prefs->GetDouble("distance4_3");
	distance3_2 = prefs->GetDouble("distance3_2");
	distance2_1 = prefs->GetDouble("distance2_1");

	tote4Max = 62;//(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
	tote3Max = 49;//(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
	tote2Max = 41;//(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
	tote1Max = 36;//(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
/*
	if (armPos >= 0){
		armMin = 0;
	} else {
		armMin = 330;
	}*/

	toteElevator4PID->SetSetpoint(std::min(tote4Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint)));
	toteElevator3PID->SetSetpoint(std::min(tote3Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)(distance4_3)*COUNTS_PER_REV/INCHES_PER_REV)));
	toteElevator2PID->SetSetpoint(std::min(tote2Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)((distance3_2 +distance4_3)*COUNTS_PER_REV/INCHES_PER_REV))));
	toteElevator1PID->SetSetpoint(std::min(tote1Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)((distance2_1+distance3_2 +distance4_3)*COUNTS_PER_REV/INCHES_PER_REV))));

}

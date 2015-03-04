#include "CompleteElevator.h"
#include "../RobotMap.h"
#include "../Commands/CompleteElevatorDefaultCommand.h"

#define SPEED (float)200
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
	lastTimeStamp = 0;
	mode = 0;

	SmartDashboard::PutNumber("Tote4-3 Distance", 14);
	SmartDashboard::PutNumber("Tote3-2 Distance", 14);
	SmartDashboard::PutNumber("Tote2-1 Distance", 14);
}

void CompleteElevator::InitDefaultCommand()
{
	SetDefaultCommand(new CompleteElevatorDefaultCommand());
}
void CompleteElevator::SetMode() {
	mode ++;
	if( mode > 2)
		mode = 0;

	if(mode == 0)
		RobotMap::i2c->Write(2, 0);
	else if(mode == 1)
		RobotMap::i2c->Write(3, 0);
	else if(mode == 2)
		RobotMap::i2c->Write(4, 0);
}

void CompleteElevator::SetMode(int Mode) {
	if(Mode >=0 && Mode <= 2)
		mode = Mode;
}
void CompleteElevator::MoveElevator(float trigger){
	//float setpoint1 = toteElevator1PID->GetSetpoint();
	//float setpoint2 = toteElevator2PID->GetSetpoint();
	//float setpoint3 = toteElevator3PID->GetSetpoint();
	//float setpoint4 = toteElevator4PID->GetSetpoint();

	float now = Timer::GetFPGATimestamp();
	float interval = now - lastTimeStamp;
	interval = std::min(0.2f, interval);
	interval = std::max(0.0f, interval);


	setpoint = std::max((float)MIN, setpoint + (trigger*SPEED*interval));

	armPos = armEncoder->GetDistance();

	if (mode == 0){  //tote stacking mode
		distance4_3 = SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = SmartDashboard::GetNumber("Tote2-1 Distance");
		tote4Max = 62;//(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 52;//(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 43;//(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 39;//(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));

	} else if (mode == 1) {  //barrel mode
		distance4_3 = 1;
		distance3_2 = 1;
		distance2_1 = 1;
		tote4Max = 62;//(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 62;//(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 62;//(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 62;//(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
	} else if (mode == 2) { // yellow tote mode
		distance4_3 = SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 1;
	}


	if (armPos >= 0){
		armMin = 0;
	} else {
		armMin = 330;
	}

	toteElevator4PID->SetSetpoint(std::min(tote4Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint)));
	toteElevator3PID->SetSetpoint(std::min(tote3Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)(distance4_3)*COUNTS_PER_REV/INCHES_PER_REV)));
	toteElevator2PID->SetSetpoint(std::min(tote2Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)((distance3_2 +distance4_3)*COUNTS_PER_REV/INCHES_PER_REV))));
	toteElevator1PID->SetSetpoint(std::min(tote1Max*COUNTS_PER_REV/INCHES_PER_REV,std::max((float)MIN, setpoint-(float)((distance2_1+distance3_2 +distance4_3)*COUNTS_PER_REV/INCHES_PER_REV))));

	lastTimeStamp = now;
}

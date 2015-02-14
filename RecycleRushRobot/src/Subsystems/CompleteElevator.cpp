#include "CompleteElevator.h"
#include "../RobotMap.h"
#include "../Commands/CompleteElevatorDefaultCommand.h"

#define DISTANCE 14
#define SPEED 4
#define COUNTS_PER_REV 120
#define INCHES_PER_REV 4
#define MAX 7000
#define MIN 0

CompleteElevator::CompleteElevator() :
		Subsystem("CompleteElevator")
{
	toteElevator1PID       = RobotMap::toteElevator1PID;
	toteElevator2PID       = RobotMap::toteElevator2PID;
	toteElevator3PID       = RobotMap::toteElevator3PID;
	toteElevator4PID       = RobotMap::toteElevator4PID;
	prefs = Preferences::GetInstance();
}

void CompleteElevator::InitDefaultCommand()
{
	SetDefaultCommand(new CompleteElevatorDefaultCommand());
}

void CompleteElevator::MoveElevator(float trigger){
	float setpoint1 = toteElevator1PID->GetSetpoint();
	float setpoint2 = toteElevator2PID->GetSetpoint();
	float setpoint3 = toteElevator3PID->GetSetpoint();
	float setpoint4 = toteElevator4PID->GetSetpoint();

	distance4_3 = prefs->GetDouble("distance4_3");
	distance3_2 = prefs->GetDouble("distance3_2");
	distance2_1 = prefs->GetDouble("distance2_1");

	toteElevator4PID->SetSetpoint(std::max((float)0, setpoint4 + (trigger*SPEED)));
			if (setpoint4 - setpoint3 > distance4_3*COUNTS_PER_REV/INCHES_PER_REV){
				toteElevator3PID->SetSetpoint(std::max((float)0, setpoint3 + (trigger*SPEED)));
			}
			if (setpoint3 - setpoint2 > distance3_2*COUNTS_PER_REV/INCHES_PER_REV){
				toteElevator2PID->SetSetpoint(std::max((float)0, setpoint2 + (trigger*SPEED)));
			}
			if (setpoint2 - setpoint1 > distance2_1*COUNTS_PER_REV/INCHES_PER_REV){
				toteElevator1PID->SetSetpoint(std::max((float)0, setpoint1 + (trigger*SPEED)));

			}
/*
	if (trigger >= 0){
		toteElevator4PID->SetSetpoint(std::min((float)MAX, setpoint4 + (trigger*SPEED)));
		if (setpoint4 - setpoint3 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV || setpoint4 >= MAX){
			toteElevator3PID->SetSetpoint(std::min((float)MAX, setpoint3 + (trigger*SPEED)));
		}
		if (setpoint3 - setpoint2 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV || setpoint3 >= MAX){
			toteElevator2PID->SetSetpoint(std::min((float)MAX, setpoint2 + (trigger*SPEED)));
		}
		if (setpoint2 - setpoint1 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV || setpoint2 >= MAX){
			toteElevator1PID->SetSetpoint(std::min((float)MAX, setpoint1 + (trigger*SPEED)));

		}
	} else if (trigger < 0){
		toteElevator1PID->SetSetpoint(std::max((float)MIN, setpoint1 + (trigger*SPEED)));
		if (setpoint2 - setpoint1 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV || setpoint1 <= MIN){
			toteElevator2PID->SetSetpoint(std::max((float)MIN, setpoint2 + (trigger*SPEED)));
		}
		if (setpoint3 - setpoint2 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV){
			toteElevator3PID->SetSetpoint(std::max((float)MIN, setpoint3 + (trigger*SPEED)));
		}
		if (setpoint4 - setpoint3 > DISTANCE*COUNTS_PER_REV/INCHES_PER_REV){
			toteElevator4PID->SetSetpoint(std::max((float)MIN, setpoint4 + (trigger*SPEED)));

		}
	}*/
}




// Put methods for controlling this subsystem
// here. Call these from Commands.

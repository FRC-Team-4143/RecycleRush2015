#include "CompleteElevator.h"
#include "../RobotMap.h"
#include "../Commands/CompleteElevatorDefaultCommand.h"

CompleteElevator::CompleteElevator() :
		Subsystem("CompleteElevator")
{
	toteElevator1PID       = RobotMap::toteElevator1PID;
	toteElevator2PID       = RobotMap::toteElevator2PID;
	toteElevator3PID       = RobotMap::toteElevator3PID;
}

void CompleteElevator::InitDefaultCommand()
{
	SetDefaultCommand(new CompleteElevatorDefaultCommand());
}

void CompleteElevator::MoveElevator(float trigger){
	float setpoint1 = toteElevator1PID->GetSetpoint();
	float setpoint2 = toteElevator2PID->GetSetpoint();
	float setpoint3 = toteElevator3PID->GetSetpoint();

	toteElevator3PID->SetSetpoint(std::max((float)0, setpoint3 + (trigger*3)));
	if (setpoint3 - setpoint2 > 15*120/4){
		toteElevator2PID->SetSetpoint(std::max((float)0, setpoint2 + (trigger*3)));

	}
	if (setpoint2 - setpoint1/497*120 > 15*120/4){
		toteElevator1PID->SetSetpoint(std::max((float)0, setpoint1 + (trigger*3*497/120)));

	}
}




// Put methods for controlling this subsystem
// here. Call these from Commands.

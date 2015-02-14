#include "Pneumatics.h"
#include "../RobotMap.h"

Pneumatics::Pneumatics() :
		Subsystem("Pneumatics")
{
	solenoid = RobotMap::testSolenoid;
}

void Pneumatics::InitDefaultCommand()
{

}

void Pneumatics::forward(){
	solenoid->Set(DoubleSolenoid::Value::kForward);
}

void Pneumatics::reverse(){
	solenoid->Set(DoubleSolenoid::Value::kReverse);
}

void Pneumatics::stop(){
	solenoid->Set(DoubleSolenoid::Value::kOff);
}

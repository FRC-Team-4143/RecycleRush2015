#include "Pneumatics.h"
#include "../RobotMap.h"

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
	theSolenoid = RobotMap::burglarSolenoid;
}

void Pneumatics::InitDefaultCommand() {
}

void Pneumatics::Forward() {
	theSolenoid->Set(DoubleSolenoid::Value::kForward);
}

void Pneumatics::Reverse() {
	theSolenoid->Set(DoubleSolenoid::Value::kReverse);
}

void Pneumatics::Stop() {
	theSolenoid->Set(DoubleSolenoid::Value::kOff);
}

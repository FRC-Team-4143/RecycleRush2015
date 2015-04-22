#include "Pneumatics.h"
#include "../RobotMap.h"
#include "../Commands/PneumaStasis.h"

Pneumatics::Pneumatics() : Subsystem("Pneumatics") {
	theSolenoid = RobotMap::burglarSolenoid;
	theLastState = DoubleSolenoid::Value::kOff;
}

void Pneumatics::InitDefaultCommand() {
	SetDefaultCommand(new PneumaStasis("PneumaStasis"));
}

void Pneumatics::Forward() {
	theLastState = DoubleSolenoid::Value::kForward;
	theSolenoid->Set(theLastState);
}

void Pneumatics::Reverse() {
	theLastState = DoubleSolenoid::Value::kReverse;
	theSolenoid->Set(theLastState);
}

void Pneumatics::Stop() {
	theLastState = DoubleSolenoid::Value::kOff;
	theSolenoid->Set(theLastState);
}

void Pneumatics::Hold() {
	theSolenoid->Set(theLastState);
}

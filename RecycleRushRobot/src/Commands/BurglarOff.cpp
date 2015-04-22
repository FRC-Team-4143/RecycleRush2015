#include "BurglarOff.h"
#include "../Robot.h"

BurglarOff::BurglarOff() {
	Requires(Robot::pneumatics);
}

void BurglarOff::Initialize() {

}

void BurglarOff::Execute() {
	Robot::pneumatics->Stop();
}

bool BurglarOff::IsFinished() {
	return true;
}

void BurglarOff::End() {
}

void BurglarOff::Interrupted() {
}

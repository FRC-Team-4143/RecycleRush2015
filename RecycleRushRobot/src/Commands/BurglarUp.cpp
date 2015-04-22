#include "BurglarUp.h"
#include "../Robot.h"

BurglarUp::BurglarUp() {
	Requires(Robot::pneumatics);
}

void BurglarUp::Initialize() {

}

void BurglarUp::Execute() {
	Robot::pneumatics->Reverse();
}

bool BurglarUp::IsFinished() {
	return true;
}

void BurglarUp::End() {
}

void BurglarUp::Interrupted() {
}

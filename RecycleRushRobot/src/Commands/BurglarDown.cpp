#include "BurglarDown.h"
#include "../Robot.h"

BurglarDown::BurglarDown() {
	Requires(Robot::pneumatics);
}

void BurglarDown::Initialize() {

}

void BurglarDown::Execute() {
	Robot::pneumatics->Forward();
}

bool BurglarDown::IsFinished() {
	return true;
}

void BurglarDown::End() {
}

void BurglarDown::Interrupted() {
}

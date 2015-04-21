#include "ReleaseClaw.h"
#include "../Robot.h"

ReleaseClaw::ReleaseClaw() {
	Requires(Robot::pneumatics);
}

void ReleaseClaw::Initialize() {

}

void ReleaseClaw::Execute() {
	Robot::pneumatics->Reverse();
}

bool ReleaseClaw::IsFinished() {
	return false;
}

void ReleaseClaw::End() {
	Robot::pneumatics->Stop();
}

void ReleaseClaw::Interrupted() {
	Robot::pneumatics->Stop();
}

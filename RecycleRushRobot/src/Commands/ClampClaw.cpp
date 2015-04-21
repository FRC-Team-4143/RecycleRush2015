#include "ClampClaw.h"
#include "../Robot.h"

ClampClaw::ClampClaw() {
	Requires(Robot::pneumatics);
}

void ClampClaw::Initialize() {

}

void ClampClaw::Execute() {
	Robot::pneumatics->Forward();
}

bool ClampClaw::IsFinished() {
	return false;
}

void ClampClaw::End() {
	Robot::pneumatics->Stop();
}

void ClampClaw::Interrupted() {
	Robot::pneumatics->Stop();
}

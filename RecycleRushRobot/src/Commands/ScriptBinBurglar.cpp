#include "ScriptBinBurglar.h"
#include "../Robot.h"
#include <iostream>

ScriptBinBurglar::ScriptBinBurglar(const char* name, float direction, float seconds)
: Command(name), _direction(direction), _seconds(seconds)
{
	std::cout << GetName() << "::ctor(" << direction << ", " << seconds << ")" << std::endl;
	Requires(Robot::pneumatics);
}

void ScriptBinBurglar::Initialize() {
	std::cout << GetName() << "::Initialize" << std::endl;
	SetTimeout(_seconds);
}

void ScriptBinBurglar::Execute() {
	if (_direction < 0) {
		Robot::pneumatics->Reverse();
	}
	else if (_direction > 0) {
		Robot::pneumatics->Forward();
	}
	else {
		Robot::pneumatics->Stop();
	}
}

bool ScriptBinBurglar::IsFinished() {
	return IsTimedOut();
}

void ScriptBinBurglar::End() {
}

void ScriptBinBurglar::Interrupted() {
}

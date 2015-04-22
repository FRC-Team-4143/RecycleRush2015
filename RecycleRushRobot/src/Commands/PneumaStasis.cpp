#include "PneumaStasis.h"
#include "../Robot.h"
#include <iostream>

PneumaStasis::PneumaStasis(const char* name)
: Command(name)
{
	std::cout << GetName() << "::ctor()" << std::endl;
	Requires(Robot::pneumatics);
}

void PneumaStasis::Initialize() {
	std::cout << GetName() << "::Initialize" << std::endl;
}

void PneumaStasis::Execute() {
	Robot::pneumatics->Hold();
}

bool PneumaStasis::IsFinished() {
	return false;
}

void PneumaStasis::End() {
}

void PneumaStasis::Interrupted() {
}

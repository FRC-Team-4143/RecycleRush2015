#ifndef TestSolenoidForward_H
#define TestSolenoidForward_H

#include "WPILib.h"

class TestSolenoidForward: public Command
{
public:
	TestSolenoidForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

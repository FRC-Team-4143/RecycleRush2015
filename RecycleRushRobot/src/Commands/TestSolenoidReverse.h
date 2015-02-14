#ifndef TestSolenoidReverse_H
#define TestSolenoidReverse_H

#include "WPILib.h"

class TestSolenoidReverse: public Command
{
public:
	TestSolenoidReverse();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef SwitchMode_H
#define SwitchMode_H

#include "WPILib.h"

class SwitchMode: public Command
{
public:
	SwitchMode();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

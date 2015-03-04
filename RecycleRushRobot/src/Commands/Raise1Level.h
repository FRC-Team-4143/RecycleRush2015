#ifndef Raise1Level_H
#define Raise1Level_H

#include "WPILib.h"

class Raise1Level: public Command
{
public:
	Raise1Level();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef PlaceStack_H
#define PlaceStack_H

#include "WPILib.h"

class PlaceStack: public Command
{
public:
	PlaceStack();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

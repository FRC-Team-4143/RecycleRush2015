#ifndef CycleLightMode_H
#define CycleLightMode_H

#include "WPILib.h"

class CycleLightMode: public Command
{
public:
	CycleLightMode();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

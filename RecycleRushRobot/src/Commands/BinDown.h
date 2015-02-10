#ifndef BinDown_H
#define BinDown_H

#include "WPILib.h"

class BinDown: public Command
{
public:
	BinDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

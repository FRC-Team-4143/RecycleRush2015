#ifndef BINARMIN_H
#define BINARMIN_H

#include "WPILib.h"

class BinArmIn: public Command
{
public:
	BinArmIn();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

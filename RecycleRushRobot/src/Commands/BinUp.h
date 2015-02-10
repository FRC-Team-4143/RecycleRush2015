#ifndef BinUp_H
#define BinUp_H

#include "WPILib.h"

class BinUp: public Command
{
public:
	BinUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

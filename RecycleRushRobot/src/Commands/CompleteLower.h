#ifndef CompleteLower_H
#define CompleteLower_H

#include "WPILib.h"

class CompleteLower: public Command
{
public:
	CompleteLower();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

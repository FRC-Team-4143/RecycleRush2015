#ifndef ResetAllEncoders_H
#define ResetAllEncoders_H

#include "WPILib.h"

class ResetAllEncoders: public Command
{
public:
	ResetAllEncoders();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

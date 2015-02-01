#ifndef SETWHEELOFFSETS_H
#define SETWHEELOFFSETS_H

#include <Commands/Command.h>

class SetWheelOffsets: public Command {
public:
	SetWheelOffsets();

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	double FLOffset;
	double FROffset;
	double RLOffset;
	double RROffset;
};

#endif

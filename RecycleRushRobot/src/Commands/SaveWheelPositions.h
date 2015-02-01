#ifndef SAVETWHEELPOSITIONS_H
#define SAVETWHEELPOSITIONS_H

#include <Commands/Command.h>

class SaveWheelPositions: public Command {
public:
	SaveWheelPositions();

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

#ifndef FIXPREFS_H
#define FIXPREFS_H

#include <Commands/Command.h>

class FixPrefs: public Command {
public:
	FixPrefs();

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

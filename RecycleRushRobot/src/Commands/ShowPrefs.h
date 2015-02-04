#ifndef SHOWPREFS_H
#define SHOWPREFS_H

#include <Commands/Command.h>

class ShowPrefs: public Command {
public:
	ShowPrefs();

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif

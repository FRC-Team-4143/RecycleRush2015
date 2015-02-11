#ifndef UPDATESMARTDASHBOARD_H
#define UPDATESMARTDASHBOARD_H

#include <Commands/Command.h>

class UpdateSmartDashboard: public Command {
public:
	UpdateSmartDashboard();

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	int pdpCurrentChannel;
};

#endif

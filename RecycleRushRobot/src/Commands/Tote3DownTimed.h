#ifndef TOTE3DOWNTIMED_H
#define TOTE3DOWNTIMED_H

#include <Commands/Command.h>

class Tote3DownTimed: public Command {
public:
	Tote3DownTimed(double seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double _seconds;
};

#endif

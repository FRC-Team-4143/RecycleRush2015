#ifndef TOTE3UPTIMED_H
#define TOTE3UPTIMED_H

#include <Commands/Command.h>

class Tote3UpTimed: public Command {
public:
	Tote3UpTimed(double seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double _seconds;
};

#endif

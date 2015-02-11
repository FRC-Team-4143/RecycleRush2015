#ifndef BINUPTIMED_H
#define BINUPTIMED_H

#include <Commands/Command.h>

class BinUpTimed: public Command {
public:
	BinUpTimed(double seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double _seconds;
};

#endif

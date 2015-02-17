#ifndef BinDownTimed_H
#define BinDownTimed_H

#include <Commands/Command.h>

class BinDownTimed: public Command {
public:
	BinDownTimed(double seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double _seconds;
};

#endif

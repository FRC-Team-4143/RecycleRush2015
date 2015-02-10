#ifndef SLEEP_H
#define SLEEP_H

#include <Commands/Command.h>

class Sleep: public Command {
public:
	Sleep(double seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	double _seconds;
};

#endif

#ifndef BINELEVATORMOVE_H
#define BINELEVATORMOVE_H

#include <Commands/Command.h>

class BinElevatorMove: public Command {
public:
	BinElevatorMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float AxisToInches(float axisValue);
};

#endif

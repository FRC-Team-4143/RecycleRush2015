#ifndef TOTEELEVATORMOVE_H
#define TOTEELEVATORMOVE_H

#include <Commands/Command.h>

class ToteElevatorMove: public Command {
public:
	ToteElevatorMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float AxisToInches(float axisValue);
};

#endif

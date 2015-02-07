#ifndef TOTEELEVATORGROUPMOVE_H
#define TOTEELEVATORGROUPMOVE_H

#include <Commands/Command.h>

class ToteElevatorGroupMove: public Command {
public:
	ToteElevatorGroupMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float AxisToInches(float axisValue);
};

#endif

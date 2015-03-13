#ifndef SETHEIGHT_H
#define SETHEIGHT_H

#include <Commands/Command.h>

class SetHeight: public Command {
public:
	SetHeight(float height, float seconds);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float _seconds;
	float _height;
};

#endif

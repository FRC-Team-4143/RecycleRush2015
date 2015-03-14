#ifndef BINARMMOVE_H
#define BINARMMOVE_H

#include <Commands/Command.h>

class BinArmMove: public Command {
public:
	BinArmMove();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
};

#endif

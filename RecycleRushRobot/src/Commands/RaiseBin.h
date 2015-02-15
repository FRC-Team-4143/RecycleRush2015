#ifndef RaiseBin_H
#define RaiseBin_H

#include "WPILib.h"

class RaiseBin: public Command
{
public:
	RaiseBin(double distance);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	double dist;
	double current;
};

#endif

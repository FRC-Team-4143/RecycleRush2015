#ifndef SCRIPTMOUSEDRIVE_H
#define SCRIPTMOUSEDRIVE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptMouseDrive: public Command
{
public:
	ScriptMouseDrive(const char* name, double x, double y, double maxspeed, double seconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double _x;
	double _y;
	double _maxspeed;
	double _seconds;
	double _angle;
	double _startingX;
	double _startingY;
	double _currentX;
	double _currentY;
};

#endif

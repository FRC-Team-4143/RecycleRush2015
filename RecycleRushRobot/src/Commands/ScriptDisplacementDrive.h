#ifndef SCRIPTDISPLACEMENTDRIVE_H
#define SCRIPTDISPLACEMENTDRIVE_H

#include <Commands/Command.h>
#include "WPILib.h"

class ScriptDisplacementDrive: public Command
{
public:
	ScriptDisplacementDrive(const char* name, double deltaX, double deltaY, double maxspeed, double timeoutSeconds);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double _deltaX;
	double _deltaY;
	double _maxspeed;
	double _timeoutSeconds;
	double _angle;
	double _startingX;
	double _startingY;
	double _targetX;
	double _targetY;
	double _currentX;
	double _currentY;
};

#endif

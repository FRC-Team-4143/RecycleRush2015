#ifndef ShowCameraDefault_H
#define ShowCameraDefault_H

#include "WPILib.h"

class ShowCameraDefault: public Command
{
public:
	ShowCameraDefault();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

#ifndef RunCamera_H
#define RunCamera_H

#include "WPILib.h"

class RunCamera: public Command
{
public:
	RunCamera(int cameraNumber);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	int cameraNum;
};

#endif

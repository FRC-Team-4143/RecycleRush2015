#ifndef SwitchCamera_H
#define SwitchCamera_H

#include "WPILib.h"

class SwitchCamera: public Command
{
public:
	SwitchCamera();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif

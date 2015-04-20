#ifndef SCRIPTROTATEBYX_H
#define SCRIPTROTATEBYX_H

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include "WPILib.h"

class ScriptRotateByX: public Command, public PIDOutput
{
public:
	ScriptRotateByX(const char* name, float rotateByDegrees, float timeoutSeconds, int stableTicksThreshold, float maxSpeed, float p);
	virtual ~ScriptRotateByX();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	// PIDOutput methods
	virtual void PIDWrite(float output);

protected:
	virtual float CalculateSetpoint() const;
	virtual float GetCurrentPosition() const;

private:
	PIDController* _pidCtrl;
	float _rotateByDegrees;
	float _timeoutSeconds;
	int _stableTicksThreshold;
	int _stableTicks;
};

#endif

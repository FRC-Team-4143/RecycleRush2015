#ifndef SCRIPTROTATEBY_H
#define SCRIPTROTATEBY_H

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include "WPILib.h"

class ScriptRotateBy: public Command, public PIDOutput
{
public:
	ScriptRotateBy(const char* name, float rotateByDegrees, float timeoutSeconds);
	virtual ~ScriptRotateBy();
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
};

#endif

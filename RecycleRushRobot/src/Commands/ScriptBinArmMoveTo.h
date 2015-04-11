#ifndef SCRIPTBINARMMOVETO_H
#define SCRIPTBINARMMOVETO_H

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include "WPILib.h"

class ScriptBinArmMoveTo: public Command, public PIDSource, public PIDOutput
{
public:
	ScriptBinArmMoveTo(const char* name, float inches, float timeoutSeconds, float maxSpeed);
	virtual ~ScriptBinArmMoveTo();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	// PIDSource methods
	virtual double PIDGet();

	// PIDOutput methods
	virtual void PIDWrite(float output);

protected:
	virtual float CalculateSetpoint() const;
	virtual float GetCurrentPosition() const;

private:
	PIDController* _pidCtrl;
	float _inches;
	float _timeoutSeconds;
};

#endif

#ifndef SCRIPTBINARMMOVEREL_H
#define SCRIPTBINARMMOVEREL_H

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>
#include "WPILib.h"

class ScriptBinArmMoveRel : public Command, public PIDSource, public PIDOutput
{
public:
	ScriptBinArmMoveRel(const char* name, float relInches, float timeoutSeconds);
	virtual ~ScriptBinArmMoveRel();
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
	float _relInches;
	float _timeoutSeconds;
};

#endif

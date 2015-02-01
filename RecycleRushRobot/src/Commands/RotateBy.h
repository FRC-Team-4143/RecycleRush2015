// ==========================================================================
// RotateBy class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#ifndef ROTATEBY_H
#define ROTATEBY_H

#include <Commands/Command.h>
#include <PIDController.h>
#include <PIDOutput.h>

// ==========================================================================

class RotateBy: public Command, public PIDOutput {
public:
	RotateBy(const char* name, double rotateByDegrees);

	// Command methods
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

	// PIDOutput methods
	virtual void PIDWrite(float output);

protected:
	virtual double CalculateSetpoint() const;
	virtual double GetCurrentPosition() const;

private:
	PIDController* _pidCtrl;
	double _rotateByDegrees;
};

// ==========================================================================

#endif

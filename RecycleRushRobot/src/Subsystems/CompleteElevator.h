#ifndef CompleteElevator_H
#define CompleteElevator_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CompleteElevator: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities

	int mode;
	int lightMode;
	int squeeze;
public:
	CompleteElevator();
	void InitDefaultCommand();
	void MoveElevator(float setpoint);
	void SetMode();
	void SetMode(int);
	void SetLED();
	void CycleLightMode();
	void Raise1Level();
	void CompleteLower();
	void ToggleSqueezeMode();
	void CancelSqueeze();
	void PlaceStack();
	void SetHeight(float);

	PIDController*     toteElevator1PID;
	PIDController*     toteElevator2PID;
	PIDController*     toteElevator3PID;
	PIDController*     toteElevator4PID;
	Encoder*		   armEncoder;

	float distance4_3;
	float distance3_2;
	float distance2_1;

	float tote4Max;
	float tote3Max;
	float tote2Max;
	float tote1Max;
	float totalMax;

	float armPos;
	float armMin;

	float lastTimeStamp;

	float setpoint;
	float offset;

	Preferences* prefs;


};

#endif

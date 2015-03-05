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
public:
	CompleteElevator();
	void InitDefaultCommand();
	void MoveElevator(float setpoint);
	void SetMode();
	void SetMode(int);
	void SetLED();

	PIDController*     toteElevator1PID;
	PIDController*     toteElevator2PID;
	PIDController*     toteElevator3PID;
	PIDController*     toteElevator4PID;
	Encoder*		   armEncoder;

	double distance4_3;
	double distance3_2;
	double distance2_1;

	float tote4Max;
	float tote3Max;
	float tote2Max;
	float tote1Max;

	double armPos;
	double armMin;

	float lastTimeStamp;

	float setpoint;
	float offset;

	Preferences* prefs;


};

#endif

#ifndef _ROBOT_H
#define _ROBOT_H

#include <WPILib.h>
#include <Commands/Command.h>
#include <LiveWindow/LiveWindow.h>
#include "Commands/AutonomousCommand.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/GyroSub.h"
#include "OI.h"

class Robot : public IterativeRobot {
public:
	Command *autonomousCommand;
	LiveWindow *lw;

	static OI *oi;
	static DriveTrain* driveTrain;
	static GyroSub* gyroSub;

	virtual void RobotInit();

	virtual void DisabledInit();
	virtual void DisabledPeriodic();

	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();

	virtual void TeleopInit();
	virtual void TeleopPeriodic();

	virtual void TestInit();
	virtual void TestPeriodic();

protected:
	void CameraInit();
	void PreferencesInit();
};

#endif

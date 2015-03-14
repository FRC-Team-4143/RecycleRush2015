#ifndef _ROBOT_H
#define _ROBOT_H

#include <Commands/AutoToteMove.h>
#include <WPILib.h>
#include <Commands/Command.h>
#include <LiveWindow/LiveWindow.h>
#include "Subsystems/BinArmSub.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/ElevatorSub.h"
#include "Subsystems/ElevatorGroupSub.h"
#include "Subsystems/ElevatorSelectorSub.h"
#include "Subsystems/GyroSub.h"
#include "Subsystems/MouseSubsystem.h"
#include "Subsystems/VisionBridgeSub.h"
#include "Subsystems/CompleteElevator.h"
#include "Subsystems/CameraSub.h"
#include "Subsystems/Pneumatics.h"
#include "OI.h"

#define USE_BINARMSUB 1

class Robot : public IterativeRobot {
public:
	Command *autonomousCommand;
	LiveWindow *lw;
	SendableChooser* autoChooser;
	static OI *oi;
	static DriveTrain* driveTrain;
	static GyroSub* gyroSub;
	static BinArmSub* binArm;
	static ElevatorSub* toteElevator1;
	static ElevatorSub* toteElevator2;
	static ElevatorSub* toteElevator3;
	static ElevatorSub* binElevator;
	static ElevatorGroupSub* toteElevatorGroup;
	static ElevatorSelectorSub* elevatorSelector;
	static CompleteElevator* completeElevator;
	//static CameraSub* camera;
	static MouseSubsystem* mouseSubsystem;
	static VisionBridgeSub* visionBridge;
	static Pneumatics* pneumatics;

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
	void ScriptInit();
};

#endif

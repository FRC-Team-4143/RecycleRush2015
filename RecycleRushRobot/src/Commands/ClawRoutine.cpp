#include "ClampClaw.h"
#include "ReleaseClaw.h"
#include "ClawRoutine.h"
#include "../Robot.h"
#include "RaiseBin.h"
#include "LowerBin.h"
#include "BinArmOut.h"
#include "BinArmIn.h"
#include "PrepareElevators.h"
#include "WaitForRelease.h"

#define COUNTS_PER_INCH 30

/*
 * This command group is made for after the barrel is picked
 * up. It will raise the barrel up to the claw, then tell
 * the claw to grip the barrel. The arm will then move down,
 * then out, then back up to push the barrel up higher while
 * it is still gripped by the claw, and support it at that
 * height
 */
ClawRoutine::ClawRoutine()
{
	Requires(Robot::completeElevator);

	//lower all elevators except for barrel
	new PrepareElevators();

	//raise barrel
	new RaiseBin(66*COUNTS_PER_INCH - RobotMap::toteElevator4PID->GetSetpoint());

	//clamp barrel with claw
	new ClampClaw();

	//lower arm
	new LowerBin(36*COUNTS_PER_INCH);

	//extend arm
	new BinArmOut(6*COUNTS_PER_INCH);

	//raise arm
	new RaiseBin(36*COUNTS_PER_INCH);

	//wait until ready to stack barrel
	new WaitForRelease();

	//allow the barrel to stack on totes
	new BinArmIn(6*COUNTS_PER_INCH);

	//release the barrel
	new ReleaseClaw();
}

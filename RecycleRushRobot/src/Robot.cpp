#include "Logger.h"
#include "Robot.h"
#include "RobotMap.h"
#include "Commands/AutonomousCommand.h"
#include "Modules/DriveTrainSettings.h"
#include "Modules/PIDParameters.h"
#include "Commands/GyroSquare.h"

OI* Robot::oi = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
GyroSub* Robot::gyroSub = nullptr;
ElevatorSub* Robot::toteElevator1 = nullptr;
ElevatorSub* Robot::toteElevator2 = nullptr;
ElevatorSub* Robot::toteElevator3 = nullptr;
ElevatorSub* Robot::binElevator = nullptr;
ElevatorSelectorSub* Robot::elevatorSelector = nullptr;

void Robot::RobotInit() {
	LOG("Robot::RobotInit");

	PreferencesInit();

	RobotMap::Init();

	// List all preferences
	auto prefs = Preferences::GetInstance();
	auto keys = prefs->GetKeys();
	std::cout << "[DEBUG] Keys:" << std::endl;
	for (auto iter = keys.begin(); iter != keys.end(); iter++) {
		auto value = prefs->GetString((*iter).c_str());
		std::cout << "[DEBUG] " << *iter << ": " << value << std::endl;
	}

	// -----------------------
	// Initialize subsystems.
	// -----------------------
	driveTrain = new DriveTrain();
	gyroSub = new GyroSub();

	#define EL1_BOTTOM     0
	#define EL1_LOAD       4
	#define EL1_TOP       60
	#define EL1_DELTA     14
	#define EL1_BOTMARGIN  2
	#define EL1_TOPMARGIN  2

	#define EL2_BOTTOM     0
	#define EL2_LOAD       4
	#define EL2_TOP       60
	#define EL2_DELTA     14
	#define EL2_BOTMARGIN  2
	#define EL2_TOPMARGIN  2

	#define EL3_BOTTOM     0
	#define EL3_LOAD       4
	#define EL3_TOP       60
	#define EL3_DELTA     14
	#define EL3_BOTMARGIN  2
	#define EL3_TOPMARGIN  2

	#define EL4_BOTTOM     0
	#define EL4_LOAD       4
	#define EL4_TOP       60
	#define EL4_DELTA     14
	#define EL4_BOTMARGIN  2
	#define EL4_TOPMARGIN  2

	PIDParameters pidParams(0.1, 0.05, 0.0125, 0); // TODO - Get parameters from Preferences? From SmartDashboard?

	toteElevator1 = new ElevatorSub("ToteElevator1", RobotMap::toteElevator1Motor, RobotMap::toteElevator1Pos, pidParams);
	toteElevator2 = new ElevatorSub("ToteElevator2", RobotMap::toteElevator2Motor, RobotMap::toteElevator2Pos, pidParams);
	toteElevator3 = new ElevatorSub("ToteElevator3", RobotMap::toteElevator3Motor, RobotMap::toteElevator3Pos, pidParams);

	toteElevator1->SetPositions(EL1_BOTTOM, EL1_LOAD, EL1_TOP, EL1_DELTA, EL1_BOTMARGIN, EL1_TOPMARGIN);
	toteElevator2->SetPositions(EL2_BOTTOM, EL2_LOAD, EL2_TOP, EL2_DELTA, EL2_BOTMARGIN, EL2_TOPMARGIN);
	toteElevator3->SetPositions(EL3_BOTTOM, EL3_LOAD, EL3_TOP, EL3_DELTA, EL3_BOTMARGIN, EL3_TOPMARGIN);

	binElevator = new ElevatorSub("BinElevator", RobotMap::binElevatorMotor, RobotMap::binElevatorPos, pidParams);

	binElevator->SetPositions(EL4_BOTTOM, EL4_LOAD, EL4_TOP, EL4_DELTA, EL4_BOTMARGIN, EL4_TOPMARGIN);

	elevatorSelector = new ElevatorSelectorSub();
	elevatorSelector->AddElevator(toteElevator1);
	elevatorSelector->AddElevator(toteElevator2);
	elevatorSelector->AddElevator(toteElevator3);
	elevatorSelector->AddElevator(binElevator);

	elevatorSelector->SelectTop();

	// ------------------------------------------------------------
	// Initialize OI *AFTER* all subsystems have been initialized.
	// ------------------------------------------------------------
	oi = new OI();
	lw = LiveWindow::GetInstance();

	// -------------------------------------------------
	// Initialize the command used for autonomous mode.
	// -------------------------------------------------
	autonomousCommand = new AutonomousCommand();

	driveTrain->SetWheelbase(21.5 / 2, 21.5 / 2, 21.5 / 2);

/*
	auto prefs = Preferences::GetInstance();
	auto FLOffset = prefs->GetDouble("FLOff");
	auto FROffset = prefs->GetDouble("FROff");
	auto RLOffset = prefs->GetDouble("RLOff");
	auto RROffset = prefs->GetDouble("RROff");
	std::cout << "Offsets(FL " << FLOffset << ", FR " << FROffset << ", RL " << RLOffset << ", RR " << RROffset << std::endl;
	driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);
*/
	DriveTrainSettings::LoadSettings();

	driveTrain->frontLeftPos->Start();
	driveTrain->frontRightPos->Start();
	driveTrain->rearLeftPos->Start();
	driveTrain->rearRightPos->Start();

	driveTrain->frontLeft->Enable();
	driveTrain->frontRight->Enable();
	driveTrain->rearLeft->Enable();
	driveTrain->rearRight->Enable();
}

// ---------------------------------------------------------
// This function is called when the Disabled button is hit.
// You can use it to reset subsystems before shutting down.
// ---------------------------------------------------------
void Robot::DisabledInit(){
	LOG("Robot::DisabledInit");
	RobotMap::i2c->Write(1, 0);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	LOG("Robot::AutonomousInit");
	autonomousCommand = new GyroSquare();
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	LOG("Robot::TeleopInit");
	// This makes sure the autonomous command stops running when
	// teleop starts running. To let autonomous continue until
	// interrupted by another command, remove the following
	// lines.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();

	Robot::driveTrain->outputLED();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {
	LOG("Robot::TestInit");
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::CameraInit() {
	LOG("Robot::CameraInit");
	auto cam = CameraServer::GetInstance();
	cam->SetQuality(50);
	cam->StartAutomaticCapture("cam0");
}

void Robot::PreferencesInit() {
	LOG("Robot::PreferencesInit");
	Preferences::GetInstance();
}

START_ROBOT_CLASS(Robot);

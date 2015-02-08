#include "Logger.h"
#include "Robot.h"
#include "RobotMap.h"
#include "Commands/AutonomousCommand.h"
#include "Modules/BinElevatorMoveFactory.h"
#include "Modules/DriveTrainSettings.h"
#include "Modules/PIDParameters.h"


OI* Robot::oi = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
GyroSub* Robot::gyroSub = nullptr;
BinArmSub* Robot::binArm = nullptr;
ElevatorSub* Robot::toteElevator1 = nullptr;
ElevatorSub* Robot::toteElevator2 = nullptr;
ElevatorSub* Robot::toteElevator3 = nullptr;
ElevatorSub* Robot::binElevator = nullptr;
ElevatorGroupSub* Robot::toteElevatorGroup = nullptr;
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

	#define BA_NEAR  0
	#define BA_FAR  20

	#define TOTE_EL1_BOTTOM     0
	#define TOTE_EL1_LOAD       4
	#define TOTE_EL1_TOP       60
	#define TOTE_EL1_DELTA     14
	#define TOTE_EL1_BOTMARGIN  2
	#define TOTE_EL1_TOPMARGIN  2

	#define TOTE_EL2_BOTTOM     0
	#define TOTE_EL2_LOAD       4
	#define TOTE_EL2_TOP       60
	#define TOTE_EL2_DELTA     14
	#define TOTE_EL2_BOTMARGIN  2
	#define TOTE_EL2_TOPMARGIN  2

	#define TOTE_EL3_BOTTOM     0
	#define TOTE_EL3_LOAD       4
	#define TOTE_EL3_TOP       60
	#define TOTE_EL3_DELTA     14
	#define TOTE_EL3_BOTMARGIN  2
	#define TOTE_EL3_TOPMARGIN  2

	#define BIN_EL_BOTTOM     0
	#define BIN_EL_LOAD       4
	#define BIN_EL_TOP       60
	#define BIN_EL_DELTA     14
	#define BIN_EL_BOTMARGIN  2
	#define BIN_EL_TOPMARGIN  2

	PIDParameters pidParams(0.1, 0.05, 0.0125, 0); // TODO - Get parameters from Preferences? From SmartDashboard?

	// ---------------
	// Create bin arm
	// ---------------
	binArm = new BinArmSub(RobotMap::binArmMotor, RobotMap::binArmPos, pidParams);

	binArm->SetPositions(BA_NEAR, BA_FAR);

	// ----------------------
	// Create tote elevators
	// ----------------------
	toteElevator1 = new ElevatorSub("ToteElevator1", RobotMap::toteElevator1Motor, RobotMap::toteElevator1Pos, pidParams);
	toteElevator2 = new ElevatorSub("ToteElevator2", RobotMap::toteElevator2Motor, RobotMap::toteElevator2Pos, pidParams);
	toteElevator3 = new ElevatorSub("ToteElevator3", RobotMap::toteElevator3Motor, RobotMap::toteElevator3Pos, pidParams);

	toteElevator1->SetEncoderDimensions(120, 4);
	toteElevator2->SetEncoderDimensions(120, 4);
	toteElevator3->SetEncoderDimensions(120, 4);

	toteElevator1->SetPositions(TOTE_EL1_BOTTOM, TOTE_EL1_LOAD, TOTE_EL1_TOP, TOTE_EL1_DELTA, TOTE_EL1_BOTMARGIN, TOTE_EL1_TOPMARGIN);
	toteElevator2->SetPositions(TOTE_EL2_BOTTOM, TOTE_EL2_LOAD, TOTE_EL2_TOP, TOTE_EL2_DELTA, TOTE_EL2_BOTMARGIN, TOTE_EL2_TOPMARGIN);
	toteElevator3->SetPositions(TOTE_EL3_BOTTOM, TOTE_EL3_LOAD, TOTE_EL3_TOP, TOTE_EL3_DELTA, TOTE_EL3_BOTMARGIN, TOTE_EL3_TOPMARGIN);

	// --------------------
	// Create bin elevator
	// --------------------
	auto binElevatorDefaultCommandFactory = new BinElevatorMoveFactory();
	binElevator = new ElevatorSub("BinElevator", RobotMap::binElevatorMotor, RobotMap::binElevatorPos, pidParams, binElevatorDefaultCommandFactory);

	binElevator->SetEncoderDimensions(120, 4);

	binElevator->SetPositions(BIN_EL_BOTTOM, BIN_EL_LOAD, BIN_EL_TOP, BIN_EL_DELTA, BIN_EL_BOTMARGIN, BIN_EL_TOPMARGIN);

	// --------------
	// Set neighbors
	// --------------
	toteElevator1->SetNeighbors(nullptr, toteElevator2);
	toteElevator2->SetNeighbors(toteElevator1, toteElevator3);
	toteElevator3->SetNeighbors(toteElevator2, binElevator);
	binElevator->SetNeighbors(toteElevator3, nullptr);

	// ----------------------------
	// Add tote elevators to group
	// ----------------------------
	toteElevatorGroup = new ElevatorGroupSub();
	toteElevatorGroup->AddElevator(toteElevator1);
	toteElevatorGroup->AddElevator(toteElevator2);
	toteElevatorGroup->AddElevator(toteElevator3);

	elevatorSelector = new ElevatorSelectorSub();
	elevatorSelector->AddElevator(toteElevator1);
	elevatorSelector->AddElevator(toteElevator2);
	elevatorSelector->AddElevator(toteElevator3);
	elevatorSelector->AddElevator(binElevator);

	elevatorSelector->SelectTop();

	// -----------------
	// Enable elevators
	// -----------------
	//toteElevator1->Enable();
	//toteElevator2->Enable();
	//toteElevator3->Enable();
	//binElevator->Enable();

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
	//autonomousCommand = new GyroSquare();
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

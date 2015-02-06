#include "Logger.h"
#include "Robot.h"
#include "RobotMap.h"
#include "Commands/AutonomousCommand.h"
#include "Modules/DriveTrainSettings.h"
#include "Modules/PIDParameters.h"

OI* Robot::oi = nullptr;
DriveTrain* Robot::driveTrain = nullptr;
GyroSub* Robot::gyroSub = nullptr;
ElevatorSub* Robot::toteElevator1 = nullptr;
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

	#define TEL1_BOT     0
	#define TEL1_LOAD   30
	#define TEL1_TOP   200
	#define TEL1_DELTA  60
	#define TEL1_BOTMARGIN  20
	#define TEL1_TOPMARGIN  20

	PIDParameters pidParams(0.1, 0.05, 0.0125, 0); // TODO - Get parameters from Preferences
	toteElevator1 = new ElevatorSub("ToteElevator1", RobotMap::toteElevator1Motor, RobotMap::toteElevator1Pos, pidParams);
	toteElevator1->SetPositions(TEL1_BOT, TEL1_LOAD, TEL1_TOP, TEL1_DELTA, TEL1_BOTMARGIN, TEL1_TOPMARGIN);

	// TODO - Define additional elevators

	elevatorSelector = new ElevatorSelectorSub();
	elevatorSelector->AddElevator(toteElevator1);

	// TODO - Add more elevators to selector

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

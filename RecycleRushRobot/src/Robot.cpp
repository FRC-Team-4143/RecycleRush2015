#include "Robot.h"
#include "RobotMap.h"
#include "Commands/AutonomousCommand.h"

OI* Robot::oi = nullptr;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;

void Robot::RobotInit() {
	std::cout << "Robot::RobotInit" << std::endl;

	PreferencesInit();

	RobotMap::Init();

	// -----------------------
	// Initialize subsystems.
	// -----------------------
	gyroSub = new GyroSub();
	driveTrain = new DriveTrain();

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

	auto prefs = Preferences::GetInstance();
	auto FLOffset = prefs->GetDouble("FLOff");
	auto FROffset = prefs->GetDouble("FROff");
	auto RLOffset = prefs->GetDouble("RLOff");
	auto RROffset = prefs->GetDouble("RROff");
	std::cout << "Offsets(FL " << FLOffset << ", FR " << FROffset << ", RL " << RLOffset << ", RR " << RROffset << std::endl;
	driveTrain->SetOffsets(FLOffset, FROffset, RLOffset, RROffset);

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
	std::cout << "Robot::DisabledInit" << std::endl;
	RobotMap::i2c->Write(1, 0);
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	std::cout << "Robot::AutonomousInit" << std::endl;
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	std::cout << "Robot::TeleopInit" << std::endl;
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
	std::cout << "Robot::TestInit" << std::endl;
	DriverStation::ReportError("Robot:TestInit -> Hello, DriverStation!");
}

void Robot::TestPeriodic() {
	lw->Run();
}

void Robot::CameraInit() {
	std::cout << "Robot::CameraInit" << std::endl;
	auto cam = CameraServer::GetInstance();
	cam->SetQuality(50);
	cam->StartAutomaticCapture("cam0");
}

void Robot::PreferencesInit() {
	std::cout << "Robot::PreferencesInit" << std::endl;
	Preferences::GetInstance();
}

START_ROBOT_CLASS(Robot);

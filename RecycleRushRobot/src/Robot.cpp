#include "Robot.h"
#include "RobotMap.h"
#include "Commands/AutonomousCommand.h"

OI* Robot::oi = nullptr;
GyroSub* Robot::gyroSub = nullptr;
DriveTrain* Robot::driveTrain = nullptr;

void Robot::RobotInit() {
	std::cout << "Robot::RobotInit" << std::endl;

	RobotMap::Init();

	// -----------------------
	// Initialize subsystems.
	// -----------------------
	gyroSub = new GyroSub();

	// ------------------------------------------------------------
	// Initialize OI *AFTER* all subsystems have been initialized.
	// ------------------------------------------------------------
	oi = new OI();
	lw = LiveWindow::GetInstance();

	// -------------------------------------------------
	// Initialize the command used for autonomous mode.
	// -------------------------------------------------
	autonomousCommand = new AutonomousCommand();
}

// ---------------------------------------------------------
// This function is called when the Disabled button is hit.
// You can use it to reset subsystems before shutting down.
// ---------------------------------------------------------
void Robot::DisabledInit(){
}

void Robot::DisabledPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	if (autonomousCommand != NULL)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure the autonomous command stops running when
	// teleop starts running. To let autonomous continue until
	// interrupted by another command, remove the following
	// lines.
	if (autonomousCommand != NULL)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TestInit() {
	std::cout << "Robot::TestInit" << std::endl;
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
	std::cout << "Robot::PreferencesInit - Getting Preferences instance" << std::endl;
	Preferences::GetInstance();
	std::cout << "Robot::PreferencesInit - Got Preferences instance" << std::endl;
}

START_ROBOT_CLASS(Robot);

#pragma once

class DoubleAutoMonitor
{
public:
	DoubleAutoMonitor();

	// Query IsDoubleAutonomous at the start of Robot::AutonomousInit to
	// determine whether to proceed. If proceeding, call OnAutonomousInit.

	// Example:
	//
	// void Robot::RobotInit() {
	//     monitor.OnRobotInit();
	//     ...
	// }
	//
	// void Robot::AutonomousInit() {
	//     if (monitor.IsDoubleAutonomous()) {
	//         return;
	//     }
	//     monitor.OnAutonomousInit();
	//     ...
	// }
	//
	// void Robot::TeleopInit() {
	//     monitor::OnTeleopInit();
	//     ....
	// }

	static bool IsCompetition();

	bool IsDoubleAutonomous() const;

	void OnRobotInit();
	void OnAutonomousInit();
	void OnTeleopInit();

private:
	enum ActiveMode {
		None = 0,
		Autonomous,
		Teleop
	};

	ActiveMode _lastActiveMode;

	DoubleAutoMonitor(const DoubleAutoMonitor& o) = delete;
	DoubleAutoMonitor& operator =(const DoubleAutoMonitor& o) = delete;
};

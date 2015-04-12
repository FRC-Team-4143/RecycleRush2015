#pragma once

class DoubleAutoMonitor
{
public:
	DoubleAutoMonitor();

	// Query SuppressAutonomous at the start of Robot::AutonomousInit to
	// determine whether to proceed. If proceeding, call OnAutonomousInit.

	// Example:
	//
	// void Robot::RobotInit() {
	//     monitor.OnRobotInit();
	//     ...
	// }
	//
	// void Robot::AutonomousInit() {
	//     if (monitor.SuppressAutonomous()) {
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

	bool SuppressAutonomous() const;

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

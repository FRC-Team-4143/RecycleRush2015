#ifndef GYROSUB_H
#define GYROSUB_H

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include "../Modules/IMUAdvanced.h"
#include "../RobotMap.h"

//
// The GyroSub subsystem represents the NAV6 accelerometer.
//
// @author JKSalmon
//
class GyroSub: public Subsystem {
private:
	// Put everything in private except methods that implement subsystem capabilities.
	IMUAdvanced* theGyro() { return RobotMap::imu; }

public:
	GyroSub();
	void InitDefaultCommand();
	double GetHeading();
	std::string GetStatus();
};

#endif

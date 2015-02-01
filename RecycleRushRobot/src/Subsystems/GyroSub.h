#ifndef GYROSUB_H
#define GYROSUB_H

#include <WPILib.h>
#include <Commands/Subsystem.h>
#include <PIDSource.h>
#include "../Modules/IMUAdvanced.h"
#include "../RobotMap.h"

//
// The GyroSub subsystem represents the NAV6 accelerometer.
//
// @author JKSalmon
//
class GyroSub: public Subsystem, public PIDSource {
private:
	// Put everything in private except methods that implement subsystem capabilities.
	IMUAdvanced* theGyro() { return RobotMap::imu; }

public:
	GyroSub();
	void InitDefaultCommand();
	double GetHeading();

	// PIDSource methods
	virtual double PIDGet();
};

#endif

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
public:
	GyroSub();

	// Subsystem methods
	virtual void InitDefaultCommand();

	// PIDSource methods
	virtual double PIDGet();

	double GetHeading();

private:
	// Put everything in private except methods that implement subsystem capabilities.
	IMUAdvanced* theGyro() { return RobotMap::imu; }
};

#endif

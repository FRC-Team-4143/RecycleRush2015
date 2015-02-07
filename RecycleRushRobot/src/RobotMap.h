#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <WPILib.h>
#include "Modules/AnalogChannelVolt.h"
#include "Modules/IMUAdvanced.h"

// The RobotMap is a mapping from the ports sensors and actuators are wired into
// to a variable name. This provides flexibility changing wiring, makes checking
// the wiring easier and significantly reduces the number of magic numbers
// floating around.

class RobotMap {
public:
    static SerialPort* serialPort;
	static IMUAdvanced* imu;
    static PowerDistributionPanel* pdp;
    static I2C* i2c;

	static PIDController*     driveTrainFrontLeft;
	static SpeedController*   driveTrainFrontLeftDrive;
	static AnalogChannelVolt* driveTrainFrontLeftPos;
	static SpeedController*   driveTrainFrontLeftSteer;

    static PIDController*     driveTrainFrontRight;
	static SpeedController*   driveTrainFrontRightDrive;
	static AnalogChannelVolt* driveTrainFrontRightPos;
	static SpeedController*   driveTrainFrontRightSteer;

	static PIDController*     driveTrainRearLeft;
	static SpeedController*   driveTrainRearLeftDrive;
	static AnalogChannelVolt* driveTrainRearLeftPos;
	static SpeedController*   driveTrainRearLeftSteer;

	static PIDController*     driveTrainRearRight;
	static SpeedController*   driveTrainRearRightDrive;
	static AnalogChannelVolt* driveTrainRearRightPos;
	static SpeedController*   driveTrainRearRightSteer;

	static SpeedController* binArmMotor;
	static Encoder*         binArmPos;

	static SpeedController* toteElevator1Motor;
	static Encoder*         toteElevator1Pos;

	static SpeedController* toteElevator2Motor;
	static Encoder*         toteElevator2Pos;

	static SpeedController* toteElevator3Motor;
	static Encoder*         toteElevator3Pos;

	static SpeedController* binElevatorMotor;
	static Encoder*         binElevatorPos;

    static void Init();
};

#endif

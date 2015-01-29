#include "RobotMap.h"
#include <LiveWindow/LiveWindow.h>

SerialPort* RobotMap::serial_port = nullptr;
IMUAdvanced* RobotMap::imu = nullptr;
PowerDistributionPanel* RobotMap::pdp = nullptr;
I2C* RobotMap::i2c = nullptr;

PIDController*     RobotMap::driveTrainFrontLeft = nullptr;
SpeedController*   RobotMap::driveTrainFrontLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontLeftPos = nullptr;
SpeedController*   RobotMap::driveTrainFrontLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainFrontRight = nullptr;
SpeedController*   RobotMap::driveTrainFrontRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainFrontRightPos = nullptr;
SpeedController*   RobotMap::driveTrainFrontRightSteer = nullptr;

PIDController*     RobotMap::driveTrainRearLeft = nullptr;
SpeedController*   RobotMap::driveTrainRearLeftDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearLeftPos = nullptr;
SpeedController*   RobotMap::driveTrainRearLeftSteer = nullptr;

PIDController*     RobotMap::driveTrainRearRight = nullptr;
SpeedController*   RobotMap::driveTrainRearRightDrive = nullptr;
AnalogChannelVolt* RobotMap::driveTrainRearRightPos = nullptr;
SpeedController*   RobotMap::driveTrainRearRightSteer = nullptr;

void RobotMap::Init() {
	std::cout << "RobotMap::Init" << std::endl;

	//LiveWindow* lw = LiveWindow::GetInstance();

	serial_port = new SerialPort(57600, SerialPort::kOnboard);
	imu = new IMUAdvanced(serial_port, 50);

	i2c = new I2C((I2C::Port) 1, 0x04 << 1);
}

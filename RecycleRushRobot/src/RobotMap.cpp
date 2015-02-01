#include "Logger.h"
#include "RobotMap.h"
#include <LiveWindow/LiveWindow.h>

SerialPort* RobotMap::serialPort = nullptr;
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

#define CONTINUOUS true
#define P 0.5
#define I 0.0
#define D 0.1
#define F 0.0
#define POTMIN 0.0
#define POTMAX 5.0
#define STEERPOW  1.0
#define TOLERANCE 0.2
#define PERIOD .02
#define RATIO 1

#define TESTSWERVE 1
#if TESTSWERVE
	#define FLD 2
	#define FLP 2
	#define FLS 6

	#define FRD 3
	#define FRP 0
	#define FRS 5

	#define RLD 1
	#define RLP 3
	#define RLS 7

	#define RRD 0
	#define RRP 1
	#define RRS 4
#else
	#define FLD 2
	#define FLP 2
	#define FLS 6

	#define FRD 3
	#define FRP 0
	#define FRS 5

	#define RLD 1
	#define RLP 3
	#define RLS 7

	#define RRD 0
	#define RRP 1
	#define RRS 4
#endif

void RobotMap::Init() {
	LOG("RobotMap::Init")

	LiveWindow* lw = LiveWindow::GetInstance();

	serialPort = new SerialPort(57600, SerialPort::kOnboard);
	imu = new IMUAdvanced(serialPort, 50);
	pdp = new PowerDistributionPanel();
	i2c = new I2C((I2C::Port) 1, 0x04 << 1);

	lw->AddSensor("IMU", "Gyro", imu);

	driveTrainFrontLeftDrive = new Talon(FLD);
	driveTrainFrontLeftPos   = new AnalogChannelVolt(FLP, true, RATIO);
	driveTrainFrontLeftSteer = new Talon(FLS);
	driveTrainFrontLeft      = new PIDController(P, I, D, F, driveTrainFrontLeftPos, driveTrainFrontLeftSteer, PERIOD);
	driveTrainFrontLeft->SetContinuous(CONTINUOUS);
	driveTrainFrontLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainFrontRightDrive = new Talon(FRD);
	driveTrainFrontRightPos   = new AnalogChannelVolt(FRP, true, RATIO);
	driveTrainFrontRightSteer = new Talon(FRS);
	driveTrainFrontRight      = new PIDController(P, I, D, F, driveTrainFrontRightPos, driveTrainFrontRightSteer, PERIOD);
	driveTrainFrontRight->SetContinuous(CONTINUOUS);
	driveTrainFrontRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontRight->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontRight->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearLeftDrive = new Talon(RLD);
	driveTrainRearLeftPos   = new AnalogChannelVolt(RLP, true, RATIO);
	driveTrainRearLeftSteer = new Talon(RLS);
	driveTrainRearLeft      = new PIDController(P, I, D, F, driveTrainRearLeftPos, driveTrainRearLeftSteer, PERIOD);
	driveTrainRearLeft->SetContinuous(CONTINUOUS);
	driveTrainRearLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainRearLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearRightDrive = new Talon(RRD);
	driveTrainRearRightPos   = new AnalogChannelVolt(RRP, true, RATIO);
	driveTrainRearRightSteer = new Talon(RRS);
	driveTrainRearRight      = new PIDController(P, I, D, F, driveTrainRearRightPos, driveTrainRearRightSteer, PERIOD);
	driveTrainRearRight->SetContinuous(CONTINUOUS);
	driveTrainRearRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearRight->SetInputRange(POTMIN, POTMAX);
	driveTrainRearRight->SetOutputRange(-STEERPOW, STEERPOW);
}

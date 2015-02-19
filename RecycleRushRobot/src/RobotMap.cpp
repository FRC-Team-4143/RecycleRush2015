#include "Logger.h"
#include "RobotMap.h"
#include "Modules/VictorWrapper.h"
#include <LiveWindow/LiveWindow.h>

SerialPort* RobotMap::serialPort = nullptr;
IMUAdvanced* RobotMap::imu = nullptr;
PowerDistributionPanel* RobotMap::pdp = nullptr;
I2C* RobotMap::i2c = nullptr;
DoubleSolenoid* RobotMap::testSolenoid = nullptr;

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



SpeedController* RobotMap::toteElevator1Motor = nullptr;
Encoder*         RobotMap::toteElevator1Pos = nullptr;
PIDController*   RobotMap::toteElevator1PID = nullptr;

SpeedController* RobotMap::toteElevator2Motor = nullptr;
Encoder*         RobotMap::toteElevator2Pos = nullptr;
PIDController*   RobotMap::toteElevator2PID = nullptr;

SpeedController* RobotMap::toteElevator3Motor = nullptr;
Encoder*         RobotMap::toteElevator3Pos = nullptr;
PIDController*   RobotMap::toteElevator3PID = nullptr;

SpeedController* RobotMap::toteElevator4Motor = nullptr;
Encoder*         RobotMap::toteElevator4Pos = nullptr;
PIDController*   RobotMap::toteElevator4PID = nullptr;

SpeedController* RobotMap::binArmMotor = nullptr;
Encoder*         RobotMap::binArmPos = nullptr;
PIDController*	 RobotMap::binArmPID = nullptr;

#define CONTINUOUS true
#define P 1.0
#define I 0.0
#define D 0.1
#define F 0.0
#define POTMIN 0.0
#define POTMAX 5.0
#define STEERPOW  1.0
#define TOLERANCE 0.2
#define PERIOD .02
#define RATIO 1
#define ELEVATOR_TOLERANCE 2

#define TESTSWERVE 0
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

	#define TOTE1_MOTOR   8
	#define TOTE1_POS_A   0
	#define TOTE1_POS_B   1
	#define TOTE1_POS_REV true

	#define TOTE2_MOTOR   9
	#define TOTE2_POS_A   2
	#define TOTE2_POS_B   3
	#define TOTE2_POS_REV false

	#define TOTE3_MOTOR   10
	#define TOTE3_POS_A   4
	#define TOTE3_POS_B   5
	#define TOTE3_POS_REV false

	#define BIN_MOTOR   11
	#define BIN_POS_A   6
	#define BIN_POS_B   7
	#define BIN_POS_REV false

	#define BINARM_MOTOR   8
	#define BINARM_POS_A   8
	#define BINARM_POS_B   9
	#define BINARM_POS_REV false
#else
	#define FLD 2
	#define FLP 2
	#define FLS 2

	#define FRD 1
	#define FRP 1
	#define FRS 4

	#define RLD 3
	#define RLP 3
	#define RLS 1

	#define RRD 0
	#define RRP 0
	#define RRS 3

	#define TOTE1_MOTOR   4
	#define TOTE1_POS_A   0
	#define TOTE1_POS_B   1
	#define TOTE1_POS_REV true
	#define TOTE1_MOTOR_REV false

	#define TOTE2_MOTOR   7
	#define TOTE2_POS_A   6
	#define TOTE2_POS_B   7
	#define TOTE2_POS_REV false
	#define TOTE2_MOTOR_REV true

	#define TOTE3_MOTOR   6
	#define TOTE3_POS_A   4
	#define TOTE3_POS_B   5
	#define TOTE3_POS_REV false
	#define TOTE3_MOTOR_REV true

	#define TOTE4_MOTOR   5
	#define TOTE4_POS_A   2
	#define TOTE4_POS_B   3
	#define TOTE4_POS_REV true
	#define TOTE4_MOTOR_REV false

	#define BINARM_MOTOR   8
	#define BINARM_POS_A   8
	#define BINARM_POS_B   9
	#define BINARM_POS_REV false
	#define BINARM_MOTOR_REV false
#endif

void RobotMap::Init() {
	LOG("RobotMap::Init");

	LiveWindow* lw = LiveWindow::GetInstance();

	serialPort = new SerialPort(57600, SerialPort::kOnboard);
	imu = new IMUAdvanced(serialPort, 50);
	pdp = new PowerDistributionPanel();
	i2c = new I2C((I2C::Port) 1, 0x04);

	lw->AddSensor("IMU", "Gyro", imu);

	testSolenoid = new DoubleSolenoid(0, 1);

//_______________________________________________________
//			Drivetrain Motors and PIDControllers
//-------------------------------------------------------

	driveTrainFrontLeftDrive = new Talon(FLD);
	driveTrainFrontLeftPos   = new AnalogChannelVolt(FLP, true, RATIO);
	driveTrainFrontLeftSteer = new CANTalon(FLS);
	driveTrainFrontLeft      = new PIDController(P, I, D, F, driveTrainFrontLeftPos, driveTrainFrontLeftSteer, PERIOD);
	driveTrainFrontLeft->SetContinuous(CONTINUOUS);
	driveTrainFrontLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainFrontRightDrive = new Talon(FRD);
	driveTrainFrontRightPos   = new AnalogChannelVolt(FRP, true, RATIO);
	driveTrainFrontRightSteer = new CANTalon(FRS);
	driveTrainFrontRight      = new PIDController(P, I, D, F, driveTrainFrontRightPos, driveTrainFrontRightSteer, PERIOD);
	driveTrainFrontRight->SetContinuous(CONTINUOUS);
	driveTrainFrontRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainFrontRight->SetInputRange(POTMIN, POTMAX);
	driveTrainFrontRight->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearLeftDrive = new Talon(RLD);
	driveTrainRearLeftPos   = new AnalogChannelVolt(RLP, true, RATIO);
	driveTrainRearLeftSteer = new CANTalon(RLS);
	driveTrainRearLeft      = new PIDController(P, I, D, F, driveTrainRearLeftPos, driveTrainRearLeftSteer, PERIOD);
	driveTrainRearLeft->SetContinuous(CONTINUOUS);
	driveTrainRearLeft->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearLeft->SetInputRange(POTMIN, POTMAX);
	driveTrainRearLeft->SetOutputRange(-STEERPOW, STEERPOW);

	driveTrainRearRightDrive = new Talon(RRD);
	driveTrainRearRightPos   = new AnalogChannelVolt(RRP, true, RATIO);
	driveTrainRearRightSteer = new CANTalon(RRS);
	driveTrainRearRight      = new PIDController(P, I, D, F, driveTrainRearRightPos, driveTrainRearRightSteer, PERIOD);
	driveTrainRearRight->SetContinuous(CONTINUOUS);
	driveTrainRearRight->SetAbsoluteTolerance(TOLERANCE);
	driveTrainRearRight->SetInputRange(POTMIN, POTMAX);
	driveTrainRearRight->SetOutputRange(-STEERPOW, STEERPOW);

//_______________________________________________________
//			Elevator Motors and PIDControllers
//-------------------------------------------------------

	toteElevator1Motor = new VictorWrapper(TOTE1_MOTOR, TOTE1_MOTOR_REV);
	toteElevator1Pos = new Encoder(TOTE1_POS_A, TOTE1_POS_B, TOTE1_POS_REV);
	toteElevator1Pos->Reset();
	toteElevator1PID      = new PIDController(0.05, 0, 0.0, 0, toteElevator1Pos, toteElevator1Motor, PERIOD);
	toteElevator1PID->SetOutputRange(-1, 1);
	toteElevator1PID->SetAbsoluteTolerance(ELEVATOR_TOLERANCE);

	toteElevator2Motor = new VictorWrapper(TOTE2_MOTOR, TOTE2_MOTOR_REV);
	toteElevator2Pos = new Encoder(TOTE2_POS_A, TOTE2_POS_B, TOTE2_POS_REV);
	toteElevator2Pos->Reset();
	toteElevator2PID      = new PIDController(0.05, 0, 0.0, 0, toteElevator2Pos, toteElevator2Motor, PERIOD);
	toteElevator2PID->SetOutputRange(-1, 1);
	toteElevator2PID->SetAbsoluteTolerance(ELEVATOR_TOLERANCE);

	//toteElevator2Motor = new Victor(BIN_MOTOR);
	//toteElevator2Pos = new Encoder(BIN_POS_A, BIN_POS_B, BIN_POS_REV);
	//toteElevator2Pos->Reset();

	toteElevator3Motor = new VictorWrapper(TOTE3_MOTOR, TOTE3_MOTOR_REV);
	toteElevator3Pos = new Encoder(TOTE3_POS_A, TOTE3_POS_B, TOTE3_POS_REV);
	toteElevator3Pos->Reset();
	toteElevator3PID      = new PIDController(0.05, 0, 0.0, 0, toteElevator3Pos, toteElevator3Motor, PERIOD);
	toteElevator3PID->SetOutputRange(-1, 1);
	toteElevator3PID->SetAbsoluteTolerance(ELEVATOR_TOLERANCE);

	toteElevator4Motor = new VictorWrapper(TOTE4_MOTOR, TOTE4_MOTOR_REV);
	toteElevator4Pos = new Encoder(TOTE4_POS_A, TOTE4_POS_B, TOTE4_POS_REV);
	toteElevator4Pos->Reset();
	toteElevator4PID      = new PIDController(0.05, 0, 0.0, 0, toteElevator4Pos, toteElevator4Motor, PERIOD);
	toteElevator4PID->SetOutputRange(-1, 1);
	toteElevator4PID->SetAbsoluteTolerance(ELEVATOR_TOLERANCE);

	binArmMotor = new VictorWrapper(BINARM_MOTOR, BINARM_MOTOR_REV);
	binArmPos = new Encoder(BINARM_POS_A, BINARM_POS_B, BINARM_POS_REV);
	binArmPos->Reset();
	binArmPID      = new PIDController(0.05, 0, 0.0, 0, binArmPos, binArmMotor, PERIOD);
	binArmPID->SetOutputRange(-0.5, 0.5);
	binArmPID->SetAbsoluteTolerance(ELEVATOR_TOLERANCE);

	//binElevatorMotor = new Victor(TOTE2_MOTOR);
	//binElevatorPos = new Encoder(TOTE2_POS_A, TOTE2_POS_B, TOTE2_POS_REV);
	//binElevatorPos->Reset();
}

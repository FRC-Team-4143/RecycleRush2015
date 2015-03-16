#include "CompleteElevator.h"
#include "../RobotMap.h"
#include "../Commands/CompleteElevatorDefaultCommand.h"

#define SPEED (float)(200*1.8)
#define COUNTS_PER_REV (float)120
#define INCHES_PER_REV (float)4
#define MIN (float)0.0
#define MULT (COUNTS_PER_REV/INCHES_PER_REV)

CompleteElevator::CompleteElevator()
: Subsystem("CompleteElevator")
{
	toteElevator1PID       = RobotMap::toteElevator1PID;
	toteElevator2PID       = RobotMap::toteElevator2PID;
	toteElevator3PID       = RobotMap::toteElevator3PID;
	toteElevator4PID       = RobotMap::toteElevator4PID;
	armEncoder			   = RobotMap::binArmPos;
	prefs = Preferences::GetInstance();
	setpoint = 0;
	lastTimeStamp = 0;
	mode = 0;
	offset = 0;
	lightMode = 0;
	squeeze = 0;

	/*
	 * Set numbers on smartdashboard based on preferences
	 *
	if (prefs->ContainsKey("distance4_3")){
		SmartDashboard::PutNumber("Tote4-3 Distance", prefs->GetDouble("distance4_3"));
	} else {
		SmartDashboard::PutNumber("Tote4-3 Distance", 14);
	}

	if (prefs->ContainsKey("distance3_2")){
		SmartDashboard::PutNumber("Tote3-2 Distance", prefs->GetDouble("distance3_2"));
	} else {
		SmartDashboard::PutNumber("Tote3-2 Distance", 14);
	}

	if (prefs->ContainsKey("distance2_1")){
		SmartDashboard::PutNumber("Tote2-1 Distance", prefs->GetDouble("distance2_1"));
	} else {
		SmartDashboard::PutNumber("Tote2-1 Distance", 14);
	}

	if (prefs->ContainsKey("tote4Max")){
		SmartDashboard::PutNumber("Tote4-Max", prefs->GetDouble("tote4Max"));
	} else {
		SmartDashboard::PutNumber("Tote4-Max", 62);
	}

	if (prefs->ContainsKey("tote3Max")){
		SmartDashboard::PutNumber("Tote3-Max", prefs->GetDouble("tote3Max"));
	} else {
		SmartDashboard::PutNumber("Tote3-Max", 52);
	}

	if (prefs->ContainsKey("tote2Max")){
		SmartDashboard::PutNumber("Tote2-Max", prefs->GetDouble("tote2Max"));
	} else {
		SmartDashboard::PutNumber("Tote2-Max", 43);
	}

	if (prefs->ContainsKey("tote1Max")){
		SmartDashboard::PutNumber("Tote1-Max", prefs->GetDouble("tote1Max"));
	} else {
		SmartDashboard::PutNumber("Tote1-Max", 39);
	}*/
}

void CompleteElevator::InitDefaultCommand()
{
	SetDefaultCommand(new CompleteElevatorDefaultCommand());
}

void CompleteElevator::CycleLightMode(){
	lightMode++;
	if (lightMode > 10) {
		lightMode = 0;
	}
	RobotMap::i2c->Write(lightMode, 0);
}

void CompleteElevator::SetMode() {
	mode ++;
	if (mode > 3)
		mode = 0;

	SetLED();
}

void CompleteElevator::SetMode(int Mode) {
	if (Mode >=0 && Mode <= 3)
		mode = Mode;
	SetLED();
}

void CompleteElevator::SetHeight(float height) {
	setpoint = height*MULT;

	MoveElevator(0);
}

void CompleteElevator::SetLED(){
	if (mode == 0 && squeeze == 0)
		RobotMap::i2c->Write(2, 0);
	else if (mode == 0)
		RobotMap::i2c->Write(5, 0);
	else if (mode == 1)
		RobotMap::i2c->Write(3, 0);
	else if (mode == 2 && squeeze == 0)
		RobotMap::i2c->Write(4, 0);
	else if (mode == 2)
		RobotMap::i2c->Write(7, 0);
	else if (mode == 3 && squeeze == 0)
		RobotMap::i2c->Write(6, 0);
	else if (mode == 3)
		RobotMap::i2c->Write(8, 0);
}

void CompleteElevator::ToggleSqueezeMode(){
	if (squeeze == 0 && (mode == 0 || mode == 2 || mode == 3)) {
		offset = -6;
		squeeze = 1;
		SetLED();
	} else {
		CancelSqueeze();
	}
	MoveElevator(0);
}

void CompleteElevator::CancelSqueeze(){
	squeeze = 0;
	offset = 0;
	SetLED();
	MoveElevator(0);
}

void CompleteElevator::Raise1Level(){
	if( mode == 0) {
		if( setpoint <= 19*MULT)
			setpoint = 20*MULT;
		else if ( setpoint <= 39 * MULT)
			setpoint = 40 * MULT;
		else if ( setpoint <= 59 * MULT)
			setpoint = 60 * MULT;
		else
			setpoint += 20*MULT;
	}
	else if( mode == 1) { // barrel mode go to step height
		setpoint = 11*MULT;
	}
	else { // barrel and tote modes
		if( setpoint <= 29*MULT)
			setpoint = 30*MULT;
		else if ( setpoint <= 49 * MULT)
			setpoint = 50 * MULT;
		else if ( setpoint <= 69 * MULT)
			setpoint = 70 * MULT;
		else
			setpoint += 20*MULT;
	}
	CancelSqueeze(); // also calls move elevator
}

void CompleteElevator::CompleteLower(){
	setpoint = 0;
	CancelSqueeze();
	MoveElevator(0);
}

void CompleteElevator::PlaceStack(){
	if (mode == 0 && setpoint > 40*30) {
		if (squeeze == 0) {
			ToggleSqueezeMode();
		}
		setpoint = 40*MULT;
	}
	MoveElevator(0);
}

void CompleteElevator::MoveElevator(float trigger){
	//float setpoint1 = toteElevator1PID->GetSetpoint();
	//float setpoint2 = toteElevator2PID->GetSetpoint();
	//float setpoint3 = toteElevator3PID->GetSetpoint();
	//float setpoint4 = toteElevator4PID->GetSetpoint();

	float now = Timer::GetFPGATimestamp();
	float interval = now - lastTimeStamp;
	interval = std::min(0.2f, interval);
	interval = std::max(0.0f, interval);

	armPos = armEncoder->GetDistance();

	if (mode == 0) { // tote stacking mode
#ifdef FOURFORKS
		distance4_3 = 18; //SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = 18; //SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 18; //SmartDashboard::GetNumber("Tote2-1 Distance");

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 53; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 43; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 33; //(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
		totalMax = tote4Max + tote1Max;
		/*
		if (trigger < 0){
			offset = -6;
		} else if (trigger > 0){
			offset = 0;
		}*/
		distance4_3 += offset;
		distance3_2 += offset;
		distance2_1 += offset;
#else
		distance4_3 = 1; //SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = 18; //SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 18; //SmartDashboard::GetNumber("Tote2-1 Distance");

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 63; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 53; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 43; //(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
		totalMax = tote4Max + tote1Max;
		/*
		if (trigger < 0){
			offset = -6;
		} else if (trigger > 0){
			offset = 0;
		}*/
		distance3_2 += offset;
		distance2_1 += offset;
#endif
	} else if (mode == 1) { // barrel mode
		distance4_3 = 0;
		distance3_2 = 0;
		distance2_1 = 0;

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 63; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 63; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 63; //(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
		totalMax = tote4Max;
	} else if (mode == 2) { // yellow tote mode
#ifdef FOURFORKS
		distance4_3 = 18; //SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = 18; //SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 0.5;

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 53; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 43; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = 43; //(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
		totalMax = tote4Max + tote1Max;

		distance4_3 += offset;
		distance3_2 += offset;
#else
		distance4_3 = 30; //SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = 18; //SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 0.5;

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 57 + 4; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = tote3Max - 4; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = tote2Max; //(float)(SmartDashboard::GetNumber("Tote1-Max"));//prefs->GetDouble("tote1Max"));
		totalMax = tote4Max + tote1Max;

		distance4_3 += offset;
		distance3_2 += offset;
#endif
	} else if (mode == 3) {
		distance4_3 = 30; //SmartDashboard::GetNumber("Tote4-3 Distance");
		distance3_2 = 18; //SmartDashboard::GetNumber("Tote3-2 Distance");
		distance2_1 = 18;

		tote4Max = 63; //(float)(SmartDashboard::GetNumber("Tote4-Max"));//prefs->GetDouble("tote4Max"));
		tote3Max = 57 + 4; //(float)(SmartDashboard::GetNumber("Tote3-Max"));//prefs->GetDouble("tote3Max"));
		tote2Max = 47 + 9; //(float)(SmartDashboard::GetNumber("Tote2-Max"));//prefs->GetDouble("tote2Max"));
		tote1Max = tote2Max - 4;
		totalMax = tote4Max + tote1Max;

		distance3_2 += offset;
		distance2_1 += offset;
	}

	if((mode == 2 || mode == 3 ) && setpoint > 50 * MULT && armEncoder->GetDistance() > 50)
		trigger = std::min((float)0.0, trigger); // don't go up too far if arm isn't back in barrel modes

	// double check these are never negative
	distance4_3 = std::max((float)MIN, distance4_3);
	distance3_2 = std::max((float)MIN, distance3_2);
	distance2_1 = std::max((float)MIN, distance2_1);

	setpoint = std::min(totalMax * MULT, std::max((float)MIN, setpoint + (trigger*SPEED*interval)));

	if (armPos >= 0) {
		armMin = 0;
	} else {
		armMin = 330;
	}

	toteElevator4PID->SetSetpoint(std::min(tote4Max*MULT,std::max((float)MIN, setpoint)));
	toteElevator3PID->SetSetpoint(std::min(tote3Max*MULT,std::max((float)MIN, setpoint-(float)(distance4_3)*MULT)));
	toteElevator2PID->SetSetpoint(std::min(tote2Max*MULT,std::max((float)MIN, setpoint-(float)((distance3_2 +distance4_3)*MULT))));
	toteElevator1PID->SetSetpoint(std::min(tote1Max*MULT,std::max((float)MIN, setpoint-(float)((distance2_1+distance3_2 +distance4_3)*MULT))));

	lastTimeStamp = now;
}

#include "VisionBridgeSub.h"
#include "../RobotMap.h"

//#include <fcntl.h>
//#include <unistd.h>
//#include <linux/input.h>

#include <condition_variable>
#include <iostream>

const uint16_t DEFAULT_LISTENING_PORT = 41430;

VisionBridgeSub::VisionBridgeSub()
:	VisionBridgeSub(DEFAULT_LISTENING_PORT)
{
}

VisionBridgeSub::VisionBridgeSub(uint16_t listeningPort)
:	Subsystem("VisionBridgeSub"),
	_mutex(),
	_listeningPort(listeningPort),
	_position(0),
	_debug(false),
	_listeningThread(&VisionBridgeSub::Listen, this)
{
	//task = new Task("VisionListener", (FUNCPTR) Listen, 100);
	//task->Start((uint32_t)this);
}

void VisionBridgeSub::InitDefaultCommand()
{
	//SetDefaultCommand(new MySpecialCommand());
}

void VisionBridgeSub::EnableDebug(bool debug) {
	_debug = debug;
}

double VisionBridgeSub::GetPosition() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	return _position;
}

void VisionBridgeSub::SetPosition(double position) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	_position = position;
	if (_debug) DebugOutput(_position);
}

void VisionBridgeSub::DebugOutput(double position) {
	std::cout << "Vision Position: " << position << std::endl;
}

void VisionBridgeSub::Listen() {
	// TODO
}

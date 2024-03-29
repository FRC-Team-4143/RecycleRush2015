#include <Subsystems/MouseSubsystem.h>
#include "../RobotMap.h"

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <condition_variable>
#include <iostream>

// to get correct permissions change this line in /etc/udev/rules.d/localextra.rules on roborio
//     SUBSYSTEM=="input", GROUP="input", MODE="660"
// to
//     SUBSYSTEM=="input", GROUP="input", MODE="666"

#define DEFAULT_MOUSE_FILE "/dev/input/event0"   // this is works if mouse is only thing plugged into USB
//#define DEFAULT_MOUSE_FILE "/dev/input/by-id/usb-Logitech_Gaming_Mouse_G402_8D93106A5252-event-mouse"

#define MOUSEDPI  240
//#define MOUSEDPI 800

MouseSubsystem::MouseSubsystem()
:	MouseSubsystem(DEFAULT_MOUSE_FILE)
{
}

MouseSubsystem::MouseSubsystem(const char* devicePath)
:	Subsystem("MouseSubsystem"),
	_mutex(),
	_devicePath(devicePath),
	_x(0), _y(0),
	_debug(false),
	_readThread(&MouseSubsystem::ReadMouse, this)
{
}

void MouseSubsystem::InitDefaultCommand()
{
	//SetDefaultCommand(new MySpecialCommand());
}

void MouseSubsystem::EnableDebug(bool debug) {
	_debug = debug;
}

// return position in inches if mouse dpi is set right
void MouseSubsystem::GetPosition(double& x, double& y) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	x = _x/MOUSEDPI;
	y = _y/MOUSEDPI;
}

void MouseSubsystem::Reset() {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	_x = _y = 0;
}

void MouseSubsystem::AddX(double delta) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	_x += delta;
	if (_debug) DebugOutput(_x, _y);
}

void MouseSubsystem::AddY(double delta) {
	std::unique_lock<std::recursive_mutex> lock(_mutex);
	_y += delta;
	if (_debug) DebugOutput(_x, _y);
}

void MouseSubsystem::DebugOutput(double x, double y) {
	std::cout << "Mouse @ " << x << ", " << y << std::endl;
}

void MouseSubsystem::ReadMouse() {
	if ((getuid ()) != 0) {
		std::cout << GetName() << ": Not root. This may not work." << std::endl;
	}

	int fd;
	if ((fd = open(_devicePath.c_str(), O_RDONLY)) == -1) {
		std::cerr << GetName() << ": Error opening mouse file." << std::endl;
		return;
	}

	struct input_event ie;
	while(read(fd, &ie, sizeof(struct input_event))) {
		if (2 == ie.type) {
			if (0 == ie.code) {
				AddX(ie.value);
			}
			else if (1 == ie.code) {
				AddY(ie.value);
			}
		}
	}

	close(fd);
}

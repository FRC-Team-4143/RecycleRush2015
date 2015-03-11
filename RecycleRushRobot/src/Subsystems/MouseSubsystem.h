#ifndef MOUSESUBSYSTEM_H
#define MOUSESUBSYSTEM_H

#include <mutex>
#include <thread>

#include "Commands/Subsystem.h"
#include "WPILib.h"

class MouseSubsystem: public Subsystem
{
public:
	// Initialize the subsystem with the default device path.
	MouseSubsystem();

	// Initialize the subsystem, specifying the device path.
	MouseSubsystem(const char* devicePath);

	void InitDefaultCommand();

	// Enable/disable debug mode. When debug is enabled, the mouse
	// position is written to standard output whenever it changes.
	void EnableDebug(bool debug);

	// Get the current position of the mouse.
	void GetPosition(double& x, double& y);

	// Reset the mouse position to 0, 0.
	void Reset();

private:
	std::recursive_mutex _mutex;
	std::string _devicePath;
	double _x;
	double _y;
	bool _debug;
	std::thread _readThread;

	void AddX(double delta);
	void AddY(double delta);
	void DebugOutput(double x, double y);
	void ReadMouse();
};

#endif

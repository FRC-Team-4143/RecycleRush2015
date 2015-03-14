#ifndef VISIONBRIDGESUB_H
#define VISIONBRIDGESUB_H

#include <mutex>
#include <thread>

#include "Commands/Subsystem.h"
#include "WPILib.h"

class VisionBridgeSub: public Subsystem
{
public:
	// Initialize the subsystem with the default UDP port.
	VisionBridgeSub();

	// Initialize the subsystem, specifying the UDP port.
	VisionBridgeSub(uint16_t listeningPort);

	void InitDefaultCommand();

	// Enable/disable debug mode. When debug is enabled,
	// received packets are written to standard output.
	void EnableDebug(bool debug);

	// Get the latest vision data.
	double GetPosition();

private:
	std::recursive_mutex _mutex;
	uint16_t _listeningPort;
	double _position;
	bool _debug;
	std::thread _listeningThread;

	void SetPosition(double position);
	void DebugOutput(double position);
	void Listen();
};

#endif

// ==========================================================================
// PDPSingleton class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-14 JKSalmon - Initial development
// 2015-02-15 JKSalmon - Added mutex to protect initialization
// ==========================================================================
#ifndef PDPSINGLETON_H
#define PDPSINGLETON_H

#include <WPILib.h>
#include <mutex>

class PDPSingleton {
public:
	static PowerDistributionPanel* GetInstance();

private:
	static std::mutex _mutex;
	static PowerDistributionPanel* _pdp;
};

#endif

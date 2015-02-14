// ==========================================================================
// PDPSingleton class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-14 JKSalmon - Initial development
// ==========================================================================
#ifndef PDPSINGLETON_H
#define PDPSINGLETON_H

#include <WPILib.h>

class PDPSingleton {
public:
	static PowerDistributionPanel* GetInstance();

private:
	static PowerDistributionPanel* _pdp;
};

#endif

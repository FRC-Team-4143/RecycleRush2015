// ==========================================================================
// ICommandFactory interface
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-07 JKSalmon - Initial development
// ==========================================================================
#ifndef ICOMMANDFACTORY_H
#define ICOMMANDFACTORY_H

#include <Commands/Command.h>

class ICommandFactory {
public:
	virtual Command* CreateCommand() = 0;
};

#endif

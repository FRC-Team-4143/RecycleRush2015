// ==========================================================================
// BinElevatorMoveFactory class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-07 JKSalmon - Initial development
// ==========================================================================
#ifndef BINELEVATORMOVEFACTORY_H
#define BINELEVATORMOVEFACTORY_H

#include "ICommandFactory.h"

class BinElevatorMoveFactory : public ICommandFactory {
public:
	virtual Command* CreateCommand();
};

#endif

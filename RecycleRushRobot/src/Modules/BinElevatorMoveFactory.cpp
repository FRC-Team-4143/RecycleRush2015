// ==========================================================================
// BinElevatorMoveFactory class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-07 JKSalmon - Initial development
// ==========================================================================
#include "BinElevatorMoveFactory.h"
#include "../Commands/BinElevatorMove.h"

Command* BinElevatorMoveFactory::CreateCommand() {
	return new BinElevatorMove();
}

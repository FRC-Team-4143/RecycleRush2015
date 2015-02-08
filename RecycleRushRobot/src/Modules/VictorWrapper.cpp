// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// ==========================================================================
#include "VictorWrapper.h"

VictorWrapper::VictorWrapper(uint32_t channel, bool invert)
: Victor(channel), _invert(invert)
{
}

void VictorWrapper::Set(float speed, uint8_t syncGroup) {
	Victor::Set(IsInvert() ? -speed : speed, syncGroup);
}

void VictorWrapper::Invert(bool invert) {
	_invert = invert;
}

bool VictorWrapper::IsInvert() const {
	return _invert;
}

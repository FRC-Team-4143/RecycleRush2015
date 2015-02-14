// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// 2015-02-14 JKSalmon - Added scaling, maximum speed, and maximum current
// ==========================================================================
#include "VictorWrapper.h"

VictorWrapper::VictorWrapper(uint32_t channel, bool invert, float scaleSpeed, float maxSpeed, uint8_t pdpChannel, double maxCurrent)
: Victor(channel), _invert(invert), _scaleSpeed(scaleSpeed), _maxSpeed(maxSpeed), _pdp(nullptr), _pdpChannel(pdpChannel), _maxCurrent(maxCurrent)
{
}

void VictorWrapper::Set(float speed, uint8_t syncGroup) {
	speed *= _scaleSpeed;
	speed = copysign(std::min<float>(fabs(speed), _maxSpeed), speed);
	if (_pdpChannel != -1 && _GetPDP()->GetCurrent(_pdpChannel) > _maxCurrent) {
		speed = 0;
	}
	Victor::Set(IsInvert() ? -speed : speed, syncGroup);
}

void VictorWrapper::Invert(bool invert) {
	_invert = invert;
}

bool VictorWrapper::IsInvert() const {
	return _invert;
}

void VictorWrapper::SetScale(float scaleSpeed) {
	_scaleSpeed = scaleSpeed;
}

float VictorWrapper::GetScale() const {
	return _scaleSpeed;
}

void VictorWrapper::SetMaxSpeed(float maxSpeed) {
	_maxSpeed = maxSpeed;
}

float VictorWrapper::GetMaxSpeed() const {
	return _maxSpeed;
}

void VictorWrapper::EnableCurrentLimit(uint8_t pdpChannel, double maxCurrent) {
	_pdpChannel = pdpChannel;
	_maxCurrent = maxCurrent;
}

void VictorWrapper::DisableCurrentLimit() {
	_pdpChannel = -1;
}

PowerDistributionPanel* VictorWrapper::_GetPDP() {
	if (_pdp == nullptr) {
		_pdp = new PowerDistributionPanel();
	}
	return _pdp;
}

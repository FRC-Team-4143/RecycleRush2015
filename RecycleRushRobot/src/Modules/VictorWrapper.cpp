// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// 2015-02-14 JKSalmon - Added scaling, maximum speed, and maximum current
// 2015-02-15 JKSalmon - Added private helper methods
// ==========================================================================
#include "VictorWrapper.h"
#include "PDPSingleton.h"

VictorWrapper::VictorWrapper(uint32_t channel, bool invertSpeed, float scaleSpeed, float maxSpeed, uint8_t pdpChannel, double maxCurrent)
: Victor(channel), _invertSpeed(invertSpeed), _scaleSpeed(scaleSpeed), _maxSpeed(maxSpeed), _pdp(nullptr), _pdpChannel(pdpChannel), _maxCurrent(maxCurrent)
{
}

void VictorWrapper::Set(float speed, uint8_t syncGroup) {
	speed = _ScaleSpeed(speed);
	speed = _LimitSpeed(speed);
	speed = _IsCurrentLimitExceeded() ? 0 : speed;
	speed = IsInverted() ? -speed : speed;
	Victor::Set(speed, syncGroup);
}

void VictorWrapper::InvertSpeed(bool invertSpeed) {
	_invertSpeed = invertSpeed;
}

bool VictorWrapper::IsInverted() const {
	return _invertSpeed;
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

double VictorWrapper::_GetCurrent() {
	return _GetPDP()->GetCurrent(_pdpChannel);
}

PowerDistributionPanel* VictorWrapper::_GetPDP() {
	if (_pdp == nullptr) {
		_pdp = PDPSingleton::GetInstance();
	}
	return _pdp;
}

// True if limiting current.
bool VictorWrapper::_IsCurrentLimitEnabled() const {
	return _pdpChannel != -1;
}

// True if the current limit has been exceeded.
bool VictorWrapper::_IsCurrentLimitExceeded() {
	return _IsCurrentLimitEnabled() && _GetCurrent() > _maxCurrent;
}

// Limit absolute speed to the configured maximum.
float VictorWrapper::_LimitSpeed(float speed) const {
	return copysign(std::min<float>(fabs(speed), _maxSpeed), speed);
}

// Scale speed by the configured factor.
float VictorWrapper::_ScaleSpeed(float speed) const {
	return speed * _scaleSpeed;
}

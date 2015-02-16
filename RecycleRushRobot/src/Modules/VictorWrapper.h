// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// 2015-02-14 JKSalmon - Added scaling, maximum speed, and maximum current
// 2015-02-15 JKSalmon - Added private helper methods
// ==========================================================================
#ifndef VICTORWRAPPER_H
#define VICTORWRAPPER_H

#include <WPILib.h>

class VictorWrapper : public Victor {
public:
	static const uint8_t INVALID_PDP_CHANNEL = static_cast<uint8_t>(-1);

	VictorWrapper(uint32_t channel, bool invertSpeed = false, float scaleSpeed = 1.0, float maxSpeed = 1.0, uint8_t pdpChannel = INVALID_PDP_CHANNEL, double maxCurrent = 10.0);

	virtual void Set(float speed, uint8_t syncGroup = 0);

	void InvertSpeed(bool invert);
	bool IsInverted() const;

	void SetScale(float scaleSpeed);
	float GetScale() const;

	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed() const;

	void EnableCurrentLimit(uint8_t pdpChannel, double maxCurrent);
	void DisableCurrentLimit();

private:
	bool _invertSpeed;
	float _scaleSpeed;
	float _maxSpeed;
	PowerDistributionPanel* _pdp;
	uint8_t _pdpChannel;
	double _maxCurrent;

	double _GetCurrent();
	PowerDistributionPanel* _GetPDP();
	bool _IsCurrentLimitEnabled() const;
	bool _IsCurrentLimitExceeded();
	float _LimitSpeed(float speed) const;
	float _ScaleSpeed(float speed) const;
};

#endif

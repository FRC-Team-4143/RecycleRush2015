// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// 2015-02-14 JKSalmon - Added scaling, maximum speed, and maximum current
// ==========================================================================
#ifndef VICTORWRAPPER_H
#define VICTORWRAPPER_H

#include <WPILib.h>

class VictorWrapper : public Victor {
public:
	VictorWrapper(uint32_t channel, bool invert = false, float scaleSpeed = 1.0, float maxSpeed = 1.0, uint8_t pdpChannel = -1, double maxCurrent = 10.0);

	virtual void Set(float speed, uint8_t syncGroup = 0);

	void Invert(bool invert);
	bool IsInvert() const;

	void SetScale(float scaleSpeed);
	float GetScale() const;

	void SetMaxSpeed(float maxSpeed);
	float GetMaxSpeed() const;

	void EnableCurrentLimit(uint8_t pdpChannel, double maxCurrent);
	void DisableCurrentLimit();

private:
	bool _invert;
	float _scaleSpeed;
	float _maxSpeed;
	PowerDistributionPanel* _pdp;
	uint8_t _pdpChannel;
	double _maxCurrent;

	PowerDistributionPanel* _GetPDP();
};

#endif

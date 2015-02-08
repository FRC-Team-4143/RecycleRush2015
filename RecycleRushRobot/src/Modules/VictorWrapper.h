// ==========================================================================
// VictorWrapper class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-08 JKSalmon - Initial development
// ==========================================================================
#ifndef VICTORWRAPPER_H
#define VICTORWRAPPER_H

#include <WPILib.h>

class VictorWrapper : public Victor {
public:
	VictorWrapper(uint32_t channel, bool invert = false);

	virtual void Set(float speed, uint8_t syncGroup = 0);

	void Invert(bool invert);
	bool IsInvert() const;

private:
	bool _invert;
};

#endif

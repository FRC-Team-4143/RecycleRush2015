// ==========================================================================
// PDPSingleton class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-14 JKSalmon - Initial development
// ==========================================================================
#include "PDPSingleton.h"

PowerDistributionPanel* PDPSingleton::_pdp = nullptr;

PowerDistributionPanel* PDPSingleton::GetInstance() {
	if (_pdp == nullptr) {
		_pdp = new PowerDistributionPanel();
	}
	return _pdp;
}

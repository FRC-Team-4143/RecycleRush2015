// ==========================================================================
// PDPSingleton class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-14 JKSalmon - Initial development
// 2015-02-15 JKSalmon - Added mutex to protect initialization
// ==========================================================================
#include "PDPSingleton.h"

std::mutex PDPSingleton::_mutex;
PowerDistributionPanel* PDPSingleton::_pdp = nullptr;

PowerDistributionPanel* PDPSingleton::GetInstance() {
	std::lock_guard<std::mutex> lck (_mutex);
	if (_pdp == nullptr) {
		_pdp = new PowerDistributionPanel();
	}
	return _pdp;
}

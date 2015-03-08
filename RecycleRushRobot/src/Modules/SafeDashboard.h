#pragma once
#include <WPILib.h>
#include <string>

class SafeDashboard
{
public:
	static std::string GetString(std::string name, std::string defaultValue);

private:
	SafeDashboard();
};


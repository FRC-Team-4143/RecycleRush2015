// ==========================================================================
// DriveTrainSettings class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#ifndef DRIVETRAINSETTINGS_H
#define DRIVETRAINSETTINGS_H

class DriveTrainSettings {
public:
	DriveTrainSettings();

	static void LoadSettings();
	static void SaveSettings();

private:
	static void LogSettings(double fl, double fr, double rl, double rr);
};

#endif

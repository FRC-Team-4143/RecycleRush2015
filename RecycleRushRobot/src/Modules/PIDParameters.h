// ==========================================================================
// PIDParameters class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#ifndef PIDPARAMETERS_H
#define PIDPARAMETERS_H

class PIDParameters {
public:
	PIDParameters(double p = 0, double i = 0, double d = 0, double f = 0);

	double P;
	double I;
	double D;
	double F;
};

#endif

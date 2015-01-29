// ==========================================================================
// Constants class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-01-10 JKSalmon - Initial development
// ==========================================================================
#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

class Constants {
public:
	Constants();
	virtual ~Constants();

	static const char* SERVO_POS_LEFT_NAME;
	static const char* SERVO_POS_MIDDLE_NAME;
	static const char* SERVO_POS_RIGHT_NAME;

	static const double SERVO_POS_LEFT_DEFAULT;
	static const double SERVO_POS_MIDDLE_DEFAULT;
	static const double SERVO_POS_RIGHT_DEFAULT;
};

#endif /* SRC_CONSTANTS_H_ */

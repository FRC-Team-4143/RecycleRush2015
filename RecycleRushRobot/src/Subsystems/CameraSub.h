#ifndef CameraSub_H
#define CameraSub_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class CameraSub: public Subsystem
{
private:

public:
	CameraSub();
	void InitDefaultCommand();
	void StartCamera(int cameraNum);
	void StopCamera(int cameraNum);
	void ShowCamera(int cameraNum);
	void SwitchCamera();

	CameraServer* server;
	IMAQdxSession sessionCam0;
	IMAQdxSession sessionCam1;
	Image *frameCam0;
	Image *frameCam1;
	IMAQdxError imaqError;
	int cameraCurrent;
	USBCamera cam0;
	USBCamera cam1;
};

#endif

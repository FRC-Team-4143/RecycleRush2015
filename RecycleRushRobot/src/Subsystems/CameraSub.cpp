#include "CameraSub.h"
#include "../RobotMap.h"
#include "../Commands/ShowCameraDefault.h"

CameraSub::CameraSub() :
		Subsystem("Camera Subsystem")
{
	frameCam0 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	frameCam1 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	CameraServer::GetInstance()->SetQuality(50);

	cameraCurrent = 0;
	StartCamera(cameraCurrent);

}

void CameraSub::InitDefaultCommand()
{
	SetDefaultCommand(new ShowCameraDefault());
}

void CameraSub::StartCamera(int cameraNum){
	if (cameraNum == 0){
		imaqError = IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &sessionCam0);
		imaqError = IMAQdxConfigureGrab(sessionCam0);
		imaqError = IMAQdxStartAcquisition(sessionCam0);

	} else if (cameraNum == 1){
		imaqError = IMAQdxOpenCamera("cam1", IMAQdxCameraControlModeController, &sessionCam1);
		imaqError = IMAQdxConfigureGrab(sessionCam1);
		imaqError = IMAQdxStartAcquisition(sessionCam1);
	}

}

void CameraSub::StopCamera(int cameraNum){
	if (cameraNum == 0){
		imaqError = IMAQdxStopAcquisition(sessionCam0);
		imaqError = IMAQdxCloseCamera(sessionCam0);

	} else if (cameraNum == 1){
		imaqError = IMAQdxStopAcquisition(sessionCam1);
		imaqError = IMAQdxCloseCamera(sessionCam1);
	}

}

void CameraSub::ShowCamera(int cameraNum){
	if (cameraNum == 0){
		imaqError = IMAQdxGrab(sessionCam0, frameCam0, true, NULL);
		CameraServer::GetInstance()->SetImage(frameCam0);

	} else if (cameraNum == 1){
		imaqError = IMAQdxGrab(sessionCam1, frameCam1, true, NULL);
		CameraServer::GetInstance()->SetImage(frameCam1);
	}
}

void CameraSub::SwitchCamera(){
	if (cameraCurrent == 0){
		StopCamera(0);
		StartCamera(1);
		cameraCurrent = 1;

	} else if (cameraCurrent == 1){
		StopCamera(1);
		StartCamera(0);
		cameraCurrent = 0;
	}
}

#include "CameraSub.h"
#include "../RobotMap.h"
#include "../Commands/ShowCameraDefault.h"

CameraSub::CameraSub() :
		Subsystem("Camera Subsystem")
{
	frameCam0 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	frameCam1 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	server = CameraServer::GetInstance();
	server->SetQuality(50);

	cameraCurrent = 0;
	StartCamera(cameraCurrent);

}

void CameraSub::InitDefaultCommand()
{
	SetDefaultCommand(new ShowCameraDefault());
}

void CameraSub::StartCamera(int cameraNum){
	if (cameraNum == 0){
		//IMAQdxSetAttribute(sessionCam0, "cam0", IMAQdxValueTypeEnumItem, IMAQdxUSBConnectionSpeedLow);
		IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &sessionCam0);
		IMAQdxConfigureGrab(sessionCam0);
		IMAQdxConfigureAcquisition(sessionCam0, true, 100);
		IMAQdxStartAcquisition(sessionCam0);

	} else if (cameraNum == 1){
		//IMAQdxSetAttribute(sessionCam1, "cam1", IMAQdxValueTypeEnumItem, IMAQdxUSBConnectionSpeedLow);
		IMAQdxOpenCamera("cam1", IMAQdxCameraControlModeController, &sessionCam1);
		IMAQdxConfigureGrab(sessionCam1);
		IMAQdxConfigureAcquisition(sessionCam1, true, 100);
		IMAQdxStartAcquisition(sessionCam1);
	}

}

void CameraSub::StopCamera(int cameraNum){
	if (cameraNum == 0){
		IMAQdxStopAcquisition(sessionCam0);
		IMAQdxCloseCamera(sessionCam0);

	} else if (cameraNum == 1){
		IMAQdxStopAcquisition(sessionCam1);
		IMAQdxCloseCamera(sessionCam1);
	}

}

void CameraSub::ShowCamera(int cameraNum){
	if (cameraNum == 0){
		IMAQdxGrab(sessionCam0, frameCam0, true, NULL);
		server->SetImage(frameCam0);

	} else if (cameraNum == 1){
		IMAQdxGrab(sessionCam1, frameCam1, true, NULL);
		server->SetImage(frameCam1);
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

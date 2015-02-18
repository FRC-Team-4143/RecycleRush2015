#include "CameraSub.h"
#include "../RobotMap.h"
#include "../Commands/ShowCameraDefault.h"
#include <USBCamera.h>

CameraSub::CameraSub() :
		Subsystem("Camera Subsystem")
, cam0("cam0", true)
, cam1("cam1", true)
{
	frameCam0 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	frameCam1 = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

	server = CameraServer::GetInstance();
	server->SetQuality(50);
	//server->StartAutomaticCapture("cam0");

	cam0.SetFPS(5);
	cam1.SetFPS(5);

	cam0.SetSize(320, 240);
	cam1.SetSize(320, 240);

//	IMAQdxEnumItem attribs[256];
//	uInt32 size;
//	IMAQdxEnumerateAttributeValues(sessionCam0, "cam0", attribs, &size);
//
//	for (int i = 0; i < size; i++)
//	{
//		printf("%s: %d\n", attribs[i].Name, attribs[i].Value);
//	}
	//IMAQdxEnumerateVideoModes()
	cameraCurrent = 0;
	//StartCamera(cameraCurrent);
}

void CameraSub::InitDefaultCommand()
{
	//SetDefaultCommand(new ShowCameraDefault());
}

void CameraSub::StartCamera(int cameraNum){
	if (cameraNum == 0){
		//IMAQdxSetAttribute(sessionCam0, "cam0", IMAQdxValueTypeEnumItem, IMAQdxUSBConnectionSpeedLow);
//		IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &sessionCam0);
//		IMAQdxConfigureGrab(sessionCam0);
//		IMAQdxConfigureAcquisition(sessionCam0, true, 100);
//		IMAQdxStartAcquisition(sessionCam0);
		cam0.OpenCamera();
		cam0.StartCapture();
	} else if (cameraNum == 1){
		//IMAQdxSetAttribute(sessionCam1, "cam1", IMAQdxValueTypeEnumItem, IMAQdxUSBConnectionSpeedLow);
//		IMAQdxOpenCamera("cam1", IMAQdxCameraControlModeController, &sessionCam1);
//		IMAQdxConfigureGrab(sessionCam1);
//		IMAQdxConfigureAcquisition(sessionCam1, true, 100);
//		IMAQdxStartAcquisition(sessionCam1);
		cam1.OpenCamera();
		cam1.StartCapture();
	}
}

void CameraSub::StopCamera(int cameraNum){
	if (cameraNum == 0){
//		IMAQdxStopAcquisition(sessionCam0);
//		IMAQdxCloseCamera(sessionCam0);
		cam0.StopCapture();
		cam0.CloseCamera();
	} else if (cameraNum == 1){
//		IMAQdxStopAcquisition(sessionCam1);
//		IMAQdxCloseCamera(sessionCam1);
		cam1.StopCapture();
		cam1.CloseCamera();
	}
}

void CameraSub::ShowCamera(int cameraNum){
	if (cameraNum == 0){
//		IMAQdxGrab(sessionCam0, frameCam0, true, NULL);
		cam0.GetImage(frameCam0);
		server->SetImage(frameCam0);
	} else if (cameraNum == 1){
		//IMAQdxGrab(sessionCam1, frameCam1, true, NULL);
		cam1.GetImage(frameCam1);
		server->SetImage(frameCam1);
	}
}

void CameraSub::SwitchCamera(){
	if (cameraCurrent == 0){
		StopCamera(0);
		StartCamera(1);
		//server->StartAutomaticCapture("cam1");
		cameraCurrent = 1;
	} else if (cameraCurrent == 1){
		StopCamera(1);
		StartCamera(0);
		//server->StartAutomaticCapture("cam0");
		cameraCurrent = 0;
	}
}

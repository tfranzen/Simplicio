#include "stdafx.h"
#include "ApogeeDriver.h"

#include <string>
#include "ApogeeDialog.h"
namespace forms2{

	/*	ref class ApogeeDialog{
		public:
			ApogeeDialog(ApogeeDriver^ driver);
		};*/

	using namespace System;
	using namespace System::Windows::Forms;
	ApogeeDriver::ApogeeDriver(void){
		/*mode = NULL_SETTING;
		trig = NULL_SETTING;
		roix1 = NULL_SETTING;
		roix2 = NULL_SETTING;
		roiy1 = NULL_SETTING;
		roiy2 = NULL_SETTING;
		hbin = NULL_SETTING;
		vbin = NULL_SETTING;*/
		AltaCamera = new ICamera2Ptr;
		framesPerImage = 1;
		exposure_time = 0.001;
		triggered = false;
	}



	int ApogeeDriver::initCamera(){
		

		ICamDiscoverPtr Discover;		// Discovery interface
		
		HRESULT 		hr;				// Return code 


		CoInitialize( NULL );			// Initialize COM library

		// Create the ICamera2 object
		hr = (*AltaCamera).CreateInstance( __uuidof( Camera2 ) );
		if ( SUCCEEDED(hr) )
		{
			OutputDebugString( L"Successfully created the ICamera2 object\n" );
		}
		else
		{
			OutputDebugString( L"Failed to create the ICamera2 object\n" );
			CoUninitialize();		// Close the COM library
			return INIT_ERROR;
		}

		// Create the ICamDiscover object
		hr = Discover.CreateInstance( __uuidof( CamDiscover ) );
		if ( SUCCEEDED(hr) )
		{
			OutputDebugString( L"Successfully created the ICamDiscover object\n" );
		}
		else
		{
			OutputDebugString( L"Failed to create the ICamDiscover object\n" );
			CoUninitialize();		// Close the COM library
			return INIT_ERROR;
		}

		// Set the checkboxes to default to searching USB 
		// interfaces for Alta cameras
		Discover->DlgCheckEthernet	= false;
		Discover->DlgCheckUsb		= true;

		// try selecting first ÚSB camera, else prompt for selection
		try{
		hr = (*AltaCamera)->Init( Apn_Interface_USB, 
			0,
			0,
			0x0 );
		}
		catch(Exception^ e){
			// Display the dialog box for finding an Alta camera
			Discover->ShowDialog( true );

			// If a camera was not selected, then release objects and exit
			if ( !Discover->ValidSelection )
			{
				OutputDebugString( L"No valid camera selection made\n" );
				Discover	= NULL;		// Release ICamDiscover COM object
				CoUninitialize();		// Close the COM library
				return NO_CAMERA;
			}

			// Initialize camera using the ICamDiscover properties
			hr = (*AltaCamera)->Init( Discover->SelectedInterface, 
				Discover->SelectedCamIdOne,
				Discover->SelectedCamIdTwo,
				0x0 );
		}

		roix1 = 0;
		roix2 = 639;
		roiy1 = 0;
		roiy2 = 479;

		(*AltaCamera)->RoiStartX = roix1;		
		(*AltaCamera)->RoiStartY = roiy1;
		(*AltaCamera)->RoiPixelsH = roix2-roix1;		
		(*AltaCamera)->RoiPixelsV = roiy2-roiy1;

		// LED A for armed, B for flushing
		(*AltaCamera)->LedMode = Apn_LedMode_EnableAll; 
		(*AltaCamera)->LedA = Apn_LedState_ExtTriggerWaiting; 
		(*AltaCamera)->LedB = Apn_LedState_Flushing;

		//(*AltaCamera)->DualReadout = true;
		

		(*AltaCamera)->DigitizationSpeed = 0; // 0 is normal, 1 is fast
		(*AltaCamera)->SequenceBulkDownload = true;
		(*AltaCamera)->ImageCount = framesPerImage;

		System::Diagnostics::Debug::WriteLine(String::Format("DualReadout: {0}",(*AltaCamera)->DualReadout));
		System::Diagnostics::Debug::WriteLine(String::Format("DigitizationSpeed: {0}",(*AltaCamera)->DigitizationSpeed));
		System::Diagnostics::Debug::WriteLine(String::Format("NumAds: {0}",(*AltaCamera)->NumAds));
		//OutputDebugString(String("Camera Model: ") +  String((char*)(*AltaCamera)->CameraModel));
		
		Discover	= NULL;		// Release Discover COM object
		return 0;
	}

	int ApogeeDriver::openCameraDialog(){
		
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 1;
		}
		ApogeeDialog^ settingsDialog = gcnew ApogeeDialog(this);
		settingsDialog->Show();
		return 0;
	}

	void ApogeeDriver::showLedDialog(){
		if((AltaCamera != NULL) || (*AltaCamera != NULL) )
			(*AltaCamera)->ShowLedDialog();
	}
	void ApogeeDriver::showIoDialog(){
		if((AltaCamera != NULL) || (*AltaCamera != NULL) )
			(*AltaCamera)->ShowIoDialog();
	}
	void ApogeeDriver::showTempDialog(){
		if((AltaCamera != NULL) || (*AltaCamera != NULL) )
			(*AltaCamera)->ShowTempDialog();
	}


	void ApogeeDriver::lockCameraDialog(bool lock){
		
	}
	void ApogeeDriver::closeCamera(){
		if((AltaCamera != NULL) && (*AltaCamera != NULL) ){
			(*AltaCamera)->Close();
		}
		CoUninitialize();	
		AltaCamera = NULL;
	}
	int ApogeeDriver::armCamera(){
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 1;
		}
		(*AltaCamera)->RoiStartX = roix1;		
		(*AltaCamera)->RoiStartY = roiy1;
		(*AltaCamera)->RoiPixelsH = roix2-roix1;		
		(*AltaCamera)->RoiPixelsV = roiy2-roiy1;
		(*AltaCamera)->ImageCount = framesPerImage;
		

		if(triggered)	(*AltaCamera)->IoPortAssignment |= 0x01;
		else			(*AltaCamera)->IoPortAssignment &= ~0x01;

		(*AltaCamera)->TriggerNormalEach = triggered;
		(*AltaCamera)->TriggerNormalGroup = false;// triggered;
		
		return 0;
	}
	void ApogeeDriver::expose(){
		
		if((AltaCamera != NULL) && (*AltaCamera != NULL) ){
			(*AltaCamera)->ImageCount = framesPerImage;
		

			if(triggered)	(*AltaCamera)->IoPortAssignment |= 0x01;
			else			(*AltaCamera)->IoPortAssignment &= ~0x01;

			(*AltaCamera)->TriggerNormalEach = triggered;
			(*AltaCamera)->TriggerNormalGroup = false;//triggered; //contrary to API doc, but seems necessary!

			System::Diagnostics::Trace::WriteLine(String::Format("Exposing for {1} frames for {0} s.", exposure_time, framesPerImage));
			int state = (*AltaCamera)->ImagingStatus;
			System::Diagnostics::Debug::WriteLine(String::Format("Camera Status: {0}", state));

			try{
			(*AltaCamera)->Expose( exposure_time , true );
			}
			catch(Exception^ e){
				System::Diagnostics::Debug::WriteLine(String::Format("Exception from Expose(): {0}", e->Message));
			}
		}
	}
	void ApogeeDriver::stop(){
		if((AltaCamera != NULL) && (*AltaCamera != NULL) ){
			(*AltaCamera)->StopExposure(false);
		}
	}
	int ApogeeDriver::getImageStatus(){
		
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return IMAGE_ERROR;
		}
		int state = (*AltaCamera)->ImagingStatus;
		
		System::Diagnostics::Trace::WriteLine(String::Format("Camera status: {0}", state));
		
		System::Diagnostics::Trace::WriteLine(String::Format("Sequence number: {0}/{1}", (*AltaCamera)->SequenceCounter, (*AltaCamera)->ImageCount));
		if(state <=0){  // error state or not initialized
			return IMAGE_ERROR;
			OutputDebugString( L"Camera in error state!\n" );
		}


		switch(state){
		
		case Apn_Status_ImageReady:
			if((*AltaCamera)->SequenceCounter== (*AltaCamera)->ImageCount)
				return CAMERA_IDLE;
			else return CAMERA_BUSY;
			break;
		default:
		case Apn_Status_ImagingActive:
		case Apn_Status_Exposing:
		case Apn_Status_Flushing:
		case Apn_Status_WaitingOnTrigger:
			return  CAMERA_BUSY;

		

		}

		
	}
	int ApogeeDriver::getImageWidth(){
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 0;
		}
		return (*AltaCamera)->RoiPixelsH;
	
	}
	int ApogeeDriver::getImageHeight(){
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 0;
		}
		return (*AltaCamera)->RoiPixelsV; //(*AltaCamera)->ImageCount * 
	}
	void ApogeeDriver::readImage(UInt16 *buffer){
		if((AltaCamera != NULL) && (*AltaCamera != NULL) ){
			while(Apn_Status_ImageReady != (*AltaCamera)->ImagingStatus){
				System::Threading::Thread::Sleep(100);
				OutputDebugString( L"Waiting for image!\n" );
			}
			(*AltaCamera)->GetImage((long) buffer);
		}
		

	}

	//settings
	int ApogeeDriver::getRows(){
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 0;
		}
		return (*AltaCamera)->ImageCount * (*AltaCamera)->RoiPixelsV;
	}

	int ApogeeDriver::getCols(){
		if((AltaCamera == NULL) || (*AltaCamera == NULL) ){
			return 0;
		}
		return (*AltaCamera)->RoiPixelsH;
	}

	bool ApogeeDriver::isDouble(){
		return false;
	}
	void ApogeeDriver::update(){

	}
	
	void ApogeeDriver::getSettings(){
	
	}


	void ApogeeDriver::setExposure(double exptime,bool trigger){
		exposure_time = exptime/1000;
		triggered = trigger;
	}

	double ApogeeDriver::getExposure(){
		return exposure_time*1000;
	}

	int ApogeeDriver::getFrames(){
		return framesPerImage;
	}
	void ApogeeDriver::setFrames(int frames){
		framesPerImage=frames;
	}



	void ApogeeDriver::setROI(int x1, int x2, int y1, int y2){
		roix1 = x1;
		roix2 = x2;
		roiy1 = y1;
		roiy2 = y2;
	}

	array<int>^ ApogeeDriver::getROI(){
		array<int>^ roi = gcnew array<int>(4);
		roi[0] = roix1;
		roi[1] = roix2;
		roi[2] = roiy1;
		roi[3] = roiy2;
		return roi;
	}

	void ApogeeDriver::setTrigger(bool trigger){
		triggered = trigger;
	}

	bool ApogeeDriver::getTrigger(){
		return triggered;
	}

	void ApogeeDriver::setLayers(int layers){
		setFrames(layers);
	}
}
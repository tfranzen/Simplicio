#include "stdafx.h"
#include "CameraThread.h"
#include "form1.h"
#include "CameraSettings.h"
#include "sencam.h"
#include "ImageData.h"
#include "SencamDriver.h"
#include "WinXDriver.h"
#include "TestDriver.h"
#include "ApogeeDriver.h"
//#include "SC2Driver.h"

//#include "cam_types.h"

namespace forms2{
	using namespace System;
	using namespace System::IO;
	using namespace System::Threading;
	
	void CameraThread::init(Form1^ f, String^ path){
		mainForm = f;
		//camDriver = (CameraDriver ^)gcnew SensicamDriver();
		setLayersReadMainWindow = gcnew DelegateInt(f,&Form1::setLayersRead);
		loopFinishedMainWindow = gcnew DelegateVoid(f,&Form1::loopFinished);
		setImgMainWindow = gcnew DelegateImg(f,&Form1::addImageData);
		
		singleFrame = f->isSingleFrame();
		camSet = new CameraSettings();
		//driver = (Driver *) new SencamDriver(); --old, now use ref class
		//driver = (Driver ^) gcnew SencamDriver();//Driver REF
		driver = (Driver ^) gcnew TestDriver();//Driver REF
		//driver = nullptr; 
		continueLock = gcnew String("");
		interruptLock = gcnew String("");
		filePath = String::Copy(path);
		saveFormat = gcnew String("aia");
		continueImageLoop = false;
		interruptImageLoop = false;
		running = false;
		cameraInited = false;
		callBack = true;
		save=false;
		nextTime = NO_TIME;
		seqVars = gcnew LinkedList<Variable^>();
	}
	String^ CameraThread::getCameraDriverName(){
		return driver->getDriverName();
	}
	int CameraThread::changeCamera(String^ camname){
		if (running || camname->Equals(driver->getDriverName()))
			return CAM_NOT_CHANGED;
		
		Driver^ newdriver=nullptr;//Driver REF
		
		if (camname->Equals(gcnew String(L"Sensicam"))){
			newdriver = (Driver ^)gcnew SencamDriver();//Driver REF
		}else if (camname->Equals(gcnew String(L"No Camera"))){
			newdriver = (Driver ^)gcnew TestDriver();
		}else if (camname->Equals(gcnew String(L"SC2 Cam"))){
			//newdriver = (Driver ^)gcnew SC2Driver();//Driver REF
			MessageBox::Show("Pixelfly not yet supported.","Simplicio",MessageBoxButtons::OK);
		}else if (camname->Equals(gcnew String(L"Princeton Instruments (WinView)"))){
//			MessageBox::Show("Attempt PI","Simplicio",MessageBoxButtons::OK);
			try{
				//MessageBox::Show("Attempt PI","Simplicio",MessageBoxButtons::OK);
				newdriver = (Driver ^)gcnew WinXDriver();
				//MessageBox::Show("Executed Constructor","Simplicio",MessageBoxButtons::OK);
			}catch (Exception ^){
				newdriver=nullptr;
				MessageBox::Show("Couldn't connect to WinView.","Simplicio",MessageBoxButtons::OK);
			}
		}else if (camname->Equals(gcnew String(L"Apogee"))){
			newdriver = (Driver ^)gcnew ApogeeDriver();
		}else{
			MessageBox::Show("Unsupported camera type requested.","Simplicio",MessageBoxButtons::OK);
		}
		
		if (newdriver != nullptr){
			//requested camera is one of the supported types
			driver->closeCamera();		
			
			//Driver* oldDriver = driver;
			//driver=newdriver;
			int err = newdriver->initCamera();
			
			if (err){
				MessageBox::Show("Error initializing camera.","Simplicio",MessageBoxButtons::OK);
				newdriver->closeCamera();
				//delete newdriver;//Driver REF
				driver->initCamera();
				return CAM_NOT_CHANGED;
			}else{
				//delete driver;//Driver REF
				driver = newdriver;
				cameraInited=true;
				return 0;
			}
		}
		/*
		if (!err){
			delete driver;
			driver = newdriver;
			return 0;
		}else{
		//error making new driver, re-initialize old driver
		driver->initCamera();
		if (newdriver != nullptr) delete newdriver;
		}
		*/
	
		return CAM_NOT_CHANGED;

	}

	void CameraThread::setPath(String^ path){
		filePath = String::Copy(path);
	}
	void CameraThread::initCamera(){
		if (running){
			MessageBox::Show("Stop the image acquisition before re-initializing the camera.","Simplicio",MessageBoxButtons::OK);
			return;
		}
		int err = driver->initCamera();
		if (!err)
		//no errors:
			cameraInited = true;
		else
			MessageBox::Show("Error initializing camera.","Simplicio",MessageBoxButtons::OK);
		
	}
	bool CameraThread::isRunning(){
		return running;
	}
	
	bool CameraThread::openCameraDialog()
	{//opens the camera settings dialogue box
	//returns false if no errors occurred
		/*
		CLOSE_DIALOG_CAM();
		if(OPEN_DIALOG_CAM(NULL,0,NULL)){
			MessageBox::Show("Error opening camera settings dialogue box.","Box",MessageBoxButtons::OK);
			return true;
		}
		return false;
		*/
		if (driver->openCameraDialog())
			return true;//errors occurred
		else
			return false;
	}

	bool CameraThread::acquire(int layers, bool runLoop){
		//start a new thread to acquire images
		//return true if something prevents the form from starting
		if (running) return true;
		if (!cameraInited){
			MessageBox::Show("Initialize camera first","Box",MessageBoxButtons::OK);return true;}
		setContinue(runLoop);
		setInterrupt(false);
		
		Thread^ acquireThread = gcnew Thread(gcnew ParameterizedThreadStart(this,&CameraThread::takeImages));
		acquireThread->Start(layers);
		return false;
	}
	void CameraThread::stop(){
		setContinue(false);
	}
	void CameraThread::interrupt(bool callback){
		callBack=callback;
		setInterrupt(true);
		setContinue(false);
	}
	void CameraThread::closeCamera(){
		/*
		STOP_COC(0);
		LOCK_DIALOG_CAM(0);//neccessary?
		CLOSE_DIALOG_CAM();
		SET_INIT(0);
		*/
		driver->closeCamera();
	}
	bool CameraThread::getContinue(){
		bool continueTemp=false;
		Monitor::Enter(continueLock);
		try{
			continueTemp = continueImageLoop;
		}
		finally{
			Monitor::Exit(continueLock);
		}
		return continueTemp;

	}
	void CameraThread::setContinue(bool c){
		Monitor::Enter(continueLock);
		try{
			continueImageLoop = c;
		}
		finally{
			Monitor::Exit(continueLock);
		}
	}
	void CameraThread::setSaveFormat(String^ format){
		//Monitor::Enter(saveFormat);
		//try{
			
			saveFormat = String::Copy(format);
		//}
		//finally{
		//	Monitor::Exit(saveFormat);
		//}
	}
	bool CameraThread::getInterrupt(){
		bool interruptTemp=false;
		Monitor::Enter(interruptLock);
		try{
			interruptTemp = interruptImageLoop;
		}
		finally{
			Monitor::Exit(interruptLock);
		}
		return interruptTemp;
	}
	void CameraThread::setInterrupt(bool c){
		Monitor::Enter(interruptLock);
		try{
			interruptImageLoop = c;
		}
		finally{
			Monitor::Exit(interruptLock);
		}
	}
	void CameraThread::finishedRunning(){
		if (callBack)
			mainForm->BeginInvoke(loopFinishedMainWindow);
		driver->lockCameraDialog(false);
		running = false;
	}
	void CameraThread::readLayers(int layersRead){
		array<Object^>^ parameters = gcnew array<Object^>(1);
		parameters[0] = layersRead;
		if (callBack)
			mainForm->BeginInvoke(setLayersReadMainWindow,parameters);
	}
	void CameraThread::gotImage(ImageData^ img){
		/*
		if (img!=nullptr)
			MessageBox::Show("Got image.","Box",MessageBoxButtons::OK);
		else
			MessageBox::Show("Got image: null","Box",MessageBoxButtons::OK);
		*/
		array<Object^>^ parameters = gcnew array<Object^>(1);
		parameters[0] = img;
		if(callBack)
			mainForm->BeginInvoke(setImgMainWindow,parameters);
	}
	void CameraThread::setSave(bool saveFiles){
		save = saveFiles;
	}

	void CameraThread::takeImages(Object^ layersObj)
	{
		const int layers = (int)layersObj;
		if(singleFrame)	driver->setLayers(layers);
		driver->lockCameraDialog(true);
		driver->armCamera();
		running=true;
		const int rows = driver->getRows();
		const int cols = driver->getCols();
		//MessageBox::Show(String::Concat("rows, cols:",rows,", ",cols),"Box",MessageBoxButtons::OK);
		const int dbl = (driver->isDouble())? 2:1;
		//MessageBox::Show(String::Concat("Doubler = ",dbl),"Box",MessageBoxButtons::OK);

		//allocate memory for the images
		UInt16 *buf = (UInt16 *)malloc(2*dbl*cols*rows*layers);
		if (buf==0){
			MessageBox::Show("Buffer memory allocation failed.","Box",MessageBoxButtons::OK);
			finishedRunning();
		}
		//driver->stop();//remove this
		
		bool runErr=false;
		do{//loop for several images
			int layersRead = 0;		
			readLayers(layersRead);
			//only expose once for single frame download on apogee
			if (singleFrame && driver->getDriverName() == "Apogee"){
				driver->expose();
			}
			//loop over each layer of the current image
			for (int lay=0;lay<layers;lay++)
			{
				//expose the CCD once for each frame, except for Apogee camera
				if (!(singleFrame && driver->getDriverName() == "Apogee")){
					driver->expose();
				}
				//int picstat;
				//int errS;
				int imgstatus;
				do{
					//errS=GET_IMAGE_STATUS(&picstat);
					imgstatus = driver->getImageStatus();
					Thread::Sleep(0);
				//}while (errS==0 && ((picstat&0x02)!=0 || (dbl==4 && (picstat&16) == 0)) && !getInterrupt());
				} while (imgstatus == Driver::CAMERA_BUSY && !getInterrupt());		 
				if (getInterrupt()) break;
				
				if (imgstatus == Driver::IMAGE_ERROR){			
					MessageBox::Show("Error while waiting for image","Box",MessageBoxButtons::OK); break;}
				if(imgstatus== Driver::CAMERA_BUSY){
					MessageBox::Show("No image","Box",MessageBoxButtons::OK); break;}
				//if (dbl==2 && (picstat&16) == 0)
				//	MessageBox::Show("One buffer empty","Box",MessageBoxButtons::OK);
				
				int width = driver->getImageWidth();
				int height = driver->getImageHeight();

				if (width != cols || height != dbl*rows){//or if width>cols etc
					MessageBox::Show(String::Format("Wrong dimensions in transfered image. Rows= {0}, Height = {1}",rows, height),"Box",MessageBoxButtons::OK);break;}
				else{				
					int bufInd = lay*width*height;
					driver->readImage(buf+bufInd);
					layersRead++;
					readLayers(layersRead);
				}
			}//end of layer for-loop
			if (layersRead==layers){//each layer read
				DateTime datetime = nextTime;
				if (datetime.Equals(NO_TIME))
					datetime = DateTime::Now;
				nextTime = NO_TIME;
				//copy the image data
				int templayers=layers;
				int temprows=rows;
				
				if (singleFrame && driver->getDriverName() == "Sensicam"){//hijacks existing code to implement this new feature
					templayers = 8;
					temprows = 128;
				}
				
				ImageData^ img = gcnew ImageData(buf,temprows,cols,templayers,(dbl==2),singleFrame,datetime); 
				img->setSeqVars(seqVars);
				seqVars->Clear();
				//save
				if (save){ //saveImage(img);
					img->saveFile(filePath,saveFormat);
				}
				//send the image to the main window
				gotImage(img);
				//saveImage(img);//(UInt16)rows*dbl,(UInt16)cols,(UInt16)layers,buf);
			}
			runErr = (layersRead!=layers);
		}while(!runErr && getContinue());
		free(buf);
		driver->stop();
		///if (runErr) MessageBox::Show("Acquisition stopped ","Box",MessageBoxButtons::OK);
		finishedRunning();
	}
	
	void CameraThread::setNextTime(DateTime nexttime){
		nextTime=nexttime;
	}
	void CameraThread::setSeqVars(LinkedList<Variable^>^ listvars){
		seqVars->Clear();
		for each(Variable^ var in listvars){
			Variable^ newvar = gcnew Variable();
			newvar->VariableValue = var->VariableValue;
			newvar->VariableName = var->VariableName;
			seqVars->AddLast(newvar);
		}
	}

	void CameraThread::setExposure(double exptime){
		if(driver)
			driver->setExposure(exptime);

	}
}
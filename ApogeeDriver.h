#ifndef APOGEE_DRIVER
#define APOGEE_DRIVER
#include "Driver.h"
#import "Apogee SDK/Apogee.dll" no_namespace rename("IFilterWheel","IFilterWheel2") 
// IFilterWheel leads to some kind of naming conflict, but we don't have one anyway...



namespace forms2{



	public ref class ApogeeDriver : Driver {
	public:
		ApogeeDriver();
		~ApogeeDriver(){}
		virtual int initCamera() override;
		virtual int openCameraDialog() override;
		virtual void lockCameraDialog(bool lock) override;
		virtual void closeCamera() override;
		virtual void expose() override;
		virtual void stop() override;
		virtual int getImageStatus() override;
		virtual int getImageWidth() override;
		virtual int getImageHeight() override;
		virtual void readImage(UInt16 *buffer) override;
		virtual String^ getDriverName() override {return gcnew String("Apogee");}
		virtual int armCamera() override;
		virtual void setExposure(double exptime,bool triggered) override;
		virtual void setLayers(int layers) override;
		//settings
		virtual int getRows() override;
		virtual int getCols() override;
		virtual bool isDouble() override;
		virtual void update() override;

		double getExposure();

		int getFrames();
		void setFrames(int frames);

		void setTrigger(bool trigger);
		bool getTrigger();

		void setROI(int x1, int x2, int y1, int y2);
		array<int>^ getROI();

		void showLedDialog();
		void showIoDialog();
		void showTempDialog();

	protected:
		int mode;
		int trig;
		ICamera2Ptr*	AltaCamera;
		//ref ICamera2Ptr	AltaCamera;		// Camera interface
		//char table[300];
		
		virtual void getSettings() override;
		int framesPerImage;
		double exposure_time;
		bool triggered;
		

	};
}
#endif
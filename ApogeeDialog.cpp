#include "StdAfx.h"
#include "ApogeeDialog.h"

namespace forms2 {
		ApogeeDialog::ApogeeDialog(ApogeeDriver^ driver)
		{
			InitializeComponent();
			cameraDriver = driver;
			ExposureBox->Value = System::Decimal(driver->getExposure());
			framesperimage->Value = System::Decimal(driver->getFrames());

			triggerCheckbox->Checked = driver->getTrigger();

			roix1->Maximum = 639;
			roix2->Maximum = 639;
			roiy1->Maximum = 479;
			roiy2->Maximum = 479;

			array<int>^ roi = driver->getROI();
			roix1->Value = System::Decimal(roi[0]);
			roix2->Value = System::Decimal(roi[1]);
			roiy1->Value = System::Decimal(roi[2]);
			roiy2->Value = System::Decimal(roi[3]);
		}

}

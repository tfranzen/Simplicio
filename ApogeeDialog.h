#pragma once
#ifndef APOGEE_DIALOG
#define APOGEE_DIALOG
#include "ApogeeDriver.h"
namespace forms2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for ApogeeDialog
	/// </summary>
	public ref class ApogeeDialog : public System::Windows::Forms::Form
	{
	
	public:
		ApogeeDialog(ApogeeDriver^ driver);

		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ApogeeDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  ExposureBox;


	private: System::Windows::Forms::NumericUpDown^  framesperimage;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  IoButtun;
	private: System::Windows::Forms::Button^  TempButton;
	private: System::Windows::Forms::Button^  LedButton;


protected:
		ApogeeDriver^ cameraDriver;
	private: System::Windows::Forms::Label^  label3;
	protected: 
	private: System::Windows::Forms::NumericUpDown^  roix1;
	private: System::Windows::Forms::NumericUpDown^  roix2;
	private: System::Windows::Forms::NumericUpDown^  roiy1;
	private: System::Windows::Forms::NumericUpDown^  roiy2;
	private: System::Windows::Forms::Button^  applyROI;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ExposureBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->framesperimage = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->IoButtun = (gcnew System::Windows::Forms::Button());
			this->TempButton = (gcnew System::Windows::Forms::Button());
			this->LedButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->roix1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->roix2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->roiy1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->roiy2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->applyROI = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ExposureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->framesperimage))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roix1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roix2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiy1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiy2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(28, 56);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(95, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Exposure time [ms]";
			this->label1->Click += gcnew System::EventHandler(this, &ApogeeDialog::label1_Click);
			// 
			// ExposureBox
			// 
			this->ExposureBox->DecimalPlaces = 1;
			this->ExposureBox->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 65536});
			this->ExposureBox->Location = System::Drawing::Point(137, 56);
			this->ExposureBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1000, 0, 0, 0});
			this->ExposureBox->Name = L"ExposureBox";
			this->ExposureBox->Size = System::Drawing::Size(67, 20);
			this->ExposureBox->TabIndex = 2;
			this->ExposureBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			this->ExposureBox->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::ExposureBox_ValueChanged);
			// 
			// framesperimage
			// 
			this->framesperimage->Location = System::Drawing::Point(137, 28);
			this->framesperimage->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->framesperimage->Name = L"framesperimage";
			this->framesperimage->Size = System::Drawing::Size(67, 20);
			this->framesperimage->TabIndex = 5;
			this->framesperimage->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->framesperimage->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::framesperimage_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(28, 30);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Frames per image";
			// 
			// IoButtun
			// 
			this->IoButtun->Location = System::Drawing::Point(31, 129);
			this->IoButtun->Name = L"IoButtun";
			this->IoButtun->Size = System::Drawing::Size(173, 29);
			this->IoButtun->TabIndex = 7;
			this->IoButtun->Text = L"IO Settings";
			this->IoButtun->UseVisualStyleBackColor = true;
			this->IoButtun->Click += gcnew System::EventHandler(this, &ApogeeDialog::IoButtun_Click);
			// 
			// TempButton
			// 
			this->TempButton->Location = System::Drawing::Point(31, 94);
			this->TempButton->Name = L"TempButton";
			this->TempButton->Size = System::Drawing::Size(173, 29);
			this->TempButton->TabIndex = 8;
			this->TempButton->Text = L"Temp Settings";
			this->TempButton->UseVisualStyleBackColor = true;
			this->TempButton->Click += gcnew System::EventHandler(this, &ApogeeDialog::TempButton_Click);
			// 
			// LedButton
			// 
			this->LedButton->Location = System::Drawing::Point(31, 164);
			this->LedButton->Name = L"LedButton";
			this->LedButton->Size = System::Drawing::Size(173, 29);
			this->LedButton->TabIndex = 9;
			this->LedButton->Text = L"LED Settings";
			this->LedButton->UseVisualStyleBackColor = true;
			this->LedButton->Click += gcnew System::EventHandler(this, &ApogeeDialog::LedButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(28, 205);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 13);
			this->label3->TabIndex = 10;
			this->label3->Text = L"ROI";
			// 
			// roix1
			// 
			this->roix1->Location = System::Drawing::Point(49, 233);
			this->roix1->Name = L"roix1";
			this->roix1->Size = System::Drawing::Size(43, 20);
			this->roix1->TabIndex = 11;
			this->roix1->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::roix1_ValueChanged);
			// 
			// roix2
			// 
			this->roix2->Location = System::Drawing::Point(98, 233);
			this->roix2->Name = L"roix2";
			this->roix2->Size = System::Drawing::Size(43, 20);
			this->roix2->TabIndex = 12;
			this->roix2->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::roix2_ValueChanged);
			// 
			// roiy1
			// 
			this->roiy1->Location = System::Drawing::Point(49, 259);
			this->roiy1->Name = L"roiy1";
			this->roiy1->Size = System::Drawing::Size(43, 20);
			this->roiy1->TabIndex = 13;
			this->roiy1->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::roiy1_ValueChanged);
			// 
			// roiy2
			// 
			this->roiy2->Location = System::Drawing::Point(98, 259);
			this->roiy2->Name = L"roiy2";
			this->roiy2->Size = System::Drawing::Size(43, 20);
			this->roiy2->TabIndex = 14;
			this->roiy2->ValueChanged += gcnew System::EventHandler(this, &ApogeeDialog::roiy2_ValueChanged);
			// 
			// applyROI
			// 
			this->applyROI->Location = System::Drawing::Point(147, 257);
			this->applyROI->Name = L"applyROI";
			this->applyROI->Size = System::Drawing::Size(51, 22);
			this->applyROI->TabIndex = 15;
			this->applyROI->Text = L"Apply";
			this->applyROI->UseVisualStyleBackColor = true;
			this->applyROI->Click += gcnew System::EventHandler(this, &ApogeeDialog::applyROI_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(31, 235);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(12, 13);
			this->label4->TabIndex = 17;
			this->label4->Text = L"x";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(31, 261);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(12, 13);
			this->label5->TabIndex = 18;
			this->label5->Text = L"y";
			// 
			// ApogeeDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(231, 333);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->applyROI);
			this->Controls->Add(this->roiy2);
			this->Controls->Add(this->roiy1);
			this->Controls->Add(this->roix2);
			this->Controls->Add(this->roix1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->LedButton);
			this->Controls->Add(this->TempButton);
			this->Controls->Add(this->IoButtun);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->framesperimage);
			this->Controls->Add(this->ExposureBox);
			this->Controls->Add(this->label1);
			this->Name = L"ApogeeDialog";
			this->Text = L"Apogee Camera Settings";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->ExposureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->framesperimage))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roix1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roix2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiy1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->roiy2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 };
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 };



			 
private: System::Void ExposureBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 
				 cameraDriver->setExposure(double(ExposureBox->Value),cameraDriver->getTrigger());
			 
		 }
private: System::Void TempButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 cameraDriver->showTempDialog();
		 }
private: System::Void IoButtun_Click(System::Object^  sender, System::EventArgs^  e) {
			 cameraDriver->showIoDialog();
		 }
private: System::Void LedButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 cameraDriver->showLedDialog();
		 }

// ensure consistency of ROI values
private: System::Void roix1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 roix2->Minimum = roix1->Value+1;
		 }
private: System::Void roix2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 roix1->Maximum = roix2->Value-1;
		 }
private: System::Void roiy1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 roiy2->Minimum = roiy1->Value+1;
		 }
private: System::Void roiy2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 roiy1->Maximum = roiy2->Value-1;
		 }


private: System::Void applyROI_Click(System::Object^  sender, System::EventArgs^  e) {
			 cameraDriver->setROI(int(roix1->Value),int(roix2->Value),int(roiy1->Value),int(roiy2->Value));
		 }
private: System::Void framesperimage_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 cameraDriver->setFrames(int(framesperimage->Value));
		 }
};
}
#endif
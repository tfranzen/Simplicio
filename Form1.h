#pragma once

namespace forms2{
#include "globalobjects.h"

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	//using namespace System::IO;
	using namespace DataStructures;
	

	
	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	
	public:
		Form1(void)
		{
			InitializeComponent();//designer-generated function
			InitProgram();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			EndProgram();
			if (components)
			{
				delete components;
			}
		}

	private: 
		System::Windows::Forms::Button^  camDialogButton;
		System::Windows::Forms::Button^  acquireButton;
	private: System::Windows::Forms::NumericUpDown^  layersBox;
	private: System::Windows::Forms::Label^  layersLabel;
	private: System::Windows::Forms::Button^  runButton;
	private: System::Windows::Forms::Button^  stopButton;
	private: System::Windows::Forms::RadioButton^  runIndicator;
	private: System::Windows::Forms::ProgressBar^  imageProgressBar;
	private: System::Windows::Forms::Button^  interruptButton;

	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::Label^  saveLabel;
	private: System::Windows::Forms::Label^  formatLabel;

	private: System::Windows::Forms::ListBox^  formatListBox;
	private: System::Windows::Forms::Button^  initButton;
	private: System::Windows::Forms::PictureBox^  pictureBox;
	private: System::Windows::Forms::ListBox^  prevListBox;
	private: System::Windows::Forms::ListBox^  frameListBox;
	private: System::Windows::Forms::Label^  stepsLabel;

	private: System::Windows::Forms::Label^  frameLabel;

	private: System::Windows::Forms::NumericUpDown^  zoomBox;
	private: System::Windows::Forms::Label^  zoomLabel;
	private: System::Windows::Forms::GroupBox^  previewGroup;
	private: System::Windows::Forms::NumericUpDown^  pixelSizeBox;
	private: System::Windows::Forms::Label^  pixelSizeLabel;
	private: System::Windows::Forms::Label^  zoomLabel2;
	private: System::Windows::Forms::CheckBox^  saveCheckBox;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::LinkLabel^  folderLabel;
	private: System::Windows::Forms::Label^  cameraLabel;
	private: System::Windows::Forms::ListBox^  cameraListBox;
	private: System::Windows::Forms::Label^  cameraNameLabel;
	private: System::Windows::Forms::CheckBox^  singleFrameCheckBox;
	private: System::Windows::Forms::TextBox^  serverNameBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  currentServerNameLabel;
	private: System::Windows::Forms::CheckBox^  normalizeCheckbox;
	private: System::Windows::Forms::CheckBox^  falseColorCheckbox;
	private: System::Windows::Forms::NumericUpDown^  scaleMaxField;







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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->camDialogButton = (gcnew System::Windows::Forms::Button());
			this->acquireButton = (gcnew System::Windows::Forms::Button());
			this->layersBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->layersLabel = (gcnew System::Windows::Forms::Label());
			this->runButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->runIndicator = (gcnew System::Windows::Forms::RadioButton());
			this->imageProgressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->interruptButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->saveLabel = (gcnew System::Windows::Forms::Label());
			this->formatLabel = (gcnew System::Windows::Forms::Label());
			this->formatListBox = (gcnew System::Windows::Forms::ListBox());
			this->initButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->prevListBox = (gcnew System::Windows::Forms::ListBox());
			this->frameListBox = (gcnew System::Windows::Forms::ListBox());
			this->stepsLabel = (gcnew System::Windows::Forms::Label());
			this->frameLabel = (gcnew System::Windows::Forms::Label());
			this->zoomBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->zoomLabel = (gcnew System::Windows::Forms::Label());
			this->previewGroup = (gcnew System::Windows::Forms::GroupBox());
			this->scaleMaxField = (gcnew System::Windows::Forms::NumericUpDown());
			this->normalizeCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->falseColorCheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->zoomLabel2 = (gcnew System::Windows::Forms::Label());
			this->pixelSizeLabel = (gcnew System::Windows::Forms::Label());
			this->pixelSizeBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->saveCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->folderLabel = (gcnew System::Windows::Forms::LinkLabel());
			this->cameraLabel = (gcnew System::Windows::Forms::Label());
			this->cameraListBox = (gcnew System::Windows::Forms::ListBox());
			this->cameraNameLabel = (gcnew System::Windows::Forms::Label());
			this->singleFrameCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->serverNameBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->currentServerNameLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->layersBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->zoomBox))->BeginInit();
			this->previewGroup->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->scaleMaxField))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pixelSizeBox))->BeginInit();
			this->SuspendLayout();
			// 
			// camDialogButton
			// 
			this->camDialogButton->Location = System::Drawing::Point(188, 107);
			this->camDialogButton->Name = L"camDialogButton";
			this->camDialogButton->Size = System::Drawing::Size(112, 32);
			this->camDialogButton->TabIndex = 0;
			this->camDialogButton->Text = L"Camera Settings";
			this->camDialogButton->UseVisualStyleBackColor = true;
			this->camDialogButton->Click += gcnew System::EventHandler(this, &Form1::camDialogButton_Click);
			// 
			// acquireButton
			// 
			this->acquireButton->Location = System::Drawing::Point(59, 278);
			this->acquireButton->Name = L"acquireButton";
			this->acquireButton->Size = System::Drawing::Size(242, 32);
			this->acquireButton->TabIndex = 1;
			this->acquireButton->Text = L"Acquire Once";
			this->acquireButton->UseVisualStyleBackColor = true;
			this->acquireButton->Click += gcnew System::EventHandler(this, &Form1::acquireButton_Click);
			// 
			// layersBox
			// 
			this->layersBox->Location = System::Drawing::Point(175, 243);
			this->layersBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->layersBox->Name = L"layersBox";
			this->layersBox->Size = System::Drawing::Size(35, 20);
			this->layersBox->TabIndex = 2;
			this->layersBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {3, 0, 0, 0});
			// 
			// layersLabel
			// 
			this->layersLabel->AutoSize = true;
			this->layersLabel->Location = System::Drawing::Point(61, 250);
			this->layersLabel->Name = L"layersLabel";
			this->layersLabel->Size = System::Drawing::Size(108, 13);
			this->layersLabel->TabIndex = 3;
			this->layersLabel->Text = L"Exposures per image:";
			// 
			// runButton
			// 
			this->runButton->Location = System::Drawing::Point(59, 327);
			this->runButton->Name = L"runButton";
			this->runButton->Size = System::Drawing::Size(242, 32);
			this->runButton->TabIndex = 4;
			this->runButton->Text = L"Acquire Repeatedly";
			this->runButton->UseVisualStyleBackColor = true;
			this->runButton->Click += gcnew System::EventHandler(this, &Form1::runButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Location = System::Drawing::Point(59, 375);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(242, 32);
			this->stopButton->TabIndex = 5;
			this->stopButton->Text = L"Stop After This Image";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &Form1::stopButton_Click);
			// 
			// runIndicator
			// 
			this->runIndicator->AutoCheck = false;
			this->runIndicator->AutoSize = true;
			this->runIndicator->Location = System::Drawing::Point(97, 481);
			this->runIndicator->Name = L"runIndicator";
			this->runIndicator->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->runIndicator->Size = System::Drawing::Size(95, 17);
			this->runIndicator->TabIndex = 6;
			this->runIndicator->Text = L"Taking Images";
			this->runIndicator->UseVisualStyleBackColor = true;
			// 
			// imageProgressBar
			// 
			this->imageProgressBar->Location = System::Drawing::Point(213, 481);
			this->imageProgressBar->Maximum = 3;
			this->imageProgressBar->Name = L"imageProgressBar";
			this->imageProgressBar->Size = System::Drawing::Size(88, 22);
			this->imageProgressBar->Step = 1;
			this->imageProgressBar->TabIndex = 7;
			// 
			// interruptButton
			// 
			this->interruptButton->Location = System::Drawing::Point(59, 422);
			this->interruptButton->Name = L"interruptButton";
			this->interruptButton->Size = System::Drawing::Size(242, 32);
			this->interruptButton->TabIndex = 8;
			this->interruptButton->Text = L"Interrupt Acquisition";
			this->interruptButton->UseVisualStyleBackColor = true;
			this->interruptButton->Click += gcnew System::EventHandler(this, &Form1::interruptButton_Click);
			// 
			// folderBrowserDialog
			// 
			this->folderBrowserDialog->Description = L"Select a folder in which to store the images.";
			this->folderBrowserDialog->RootFolder = System::Environment::SpecialFolder::MyComputer;
			this->folderBrowserDialog->HelpRequest += gcnew System::EventHandler(this, &Form1::folderBrowserDialog_HelpRequest);
			// 
			// saveLabel
			// 
			this->saveLabel->AutoSize = true;
			this->saveLabel->Location = System::Drawing::Point(15, 13);
			this->saveLabel->Name = L"saveLabel";
			this->saveLabel->Size = System::Drawing::Size(47, 13);
			this->saveLabel->TabIndex = 10;
			this->saveLabel->Text = L"Save to:";
			// 
			// formatLabel
			// 
			this->formatLabel->AutoSize = true;
			this->formatLabel->Location = System::Drawing::Point(15, 66);
			this->formatLabel->Name = L"formatLabel";
			this->formatLabel->Size = System::Drawing::Size(61, 13);
			this->formatLabel->TabIndex = 11;
			this->formatLabel->Text = L"File Format:";
			// 
			// formatListBox
			// 
			this->formatListBox->ColumnWidth = 25;
			this->formatListBox->FormattingEnabled = true;
			this->formatListBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"aia", L"h5", L"tif", L"dus"});
			this->formatListBox->Location = System::Drawing::Point(82, 66);
			this->formatListBox->MultiColumn = true;
			this->formatListBox->Name = L"formatListBox";
			this->formatListBox->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->formatListBox->Size = System::Drawing::Size(136, 17);
			this->formatListBox->TabIndex = 13;
			this->formatListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::formatListBox_SelectedIndexChanged);
			// 
			// initButton
			// 
			this->initButton->Location = System::Drawing::Point(61, 107);
			this->initButton->Name = L"initButton";
			this->initButton->Size = System::Drawing::Size(112, 32);
			this->initButton->TabIndex = 14;
			this->initButton->Text = L"Initialize Camera";
			this->initButton->UseVisualStyleBackColor = true;
			this->initButton->Click += gcnew System::EventHandler(this, &Form1::initButton_Click);
			// 
			// pictureBox
			// 
			this->pictureBox->BackColor = System::Drawing::Color::Black;
			this->pictureBox->Location = System::Drawing::Point(369, 42);
			this->pictureBox->Name = L"pictureBox";
			this->pictureBox->Size = System::Drawing::Size(878, 927);
			this->pictureBox->TabIndex = 15;
			this->pictureBox->TabStop = false;
			// 
			// prevListBox
			// 
			this->prevListBox->FormattingEnabled = true;
			this->prevListBox->Items->AddRange(gcnew cli::array< System::Object^  >(20) {L"0", L"1", L"2", L"3", L"4", L"5", L"6", L"7", 
				L"8", L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19"});
			this->prevListBox->Location = System::Drawing::Point(61, 591);
			this->prevListBox->Name = L"prevListBox";
			this->prevListBox->Size = System::Drawing::Size(73, 147);
			this->prevListBox->TabIndex = 16;
			this->prevListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::prevListBox_SelectedIndexChanged);
			// 
			// frameListBox
			// 
			this->frameListBox->FormattingEnabled = true;
			this->frameListBox->Items->AddRange(gcnew cli::array< System::Object^  >(10) {L"Absorption Image", L"Probe With Atoms", L"Probe Without Atoms", 
				L"Dark Field", L"4", L"5", L"6", L"7", L"8", L"9"});
			this->frameListBox->Location = System::Drawing::Point(119, 58);
			this->frameListBox->Name = L"frameListBox";
			this->frameListBox->Size = System::Drawing::Size(140, 82);
			this->frameListBox->TabIndex = 17;
			this->frameListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::frameListBox_SelectedIndexChanged);
			// 
			// stepsLabel
			// 
			this->stepsLabel->AutoSize = true;
			this->stepsLabel->Location = System::Drawing::Point(58, 570);
			this->stepsLabel->Name = L"stepsLabel";
			this->stepsLabel->Size = System::Drawing::Size(64, 13);
			this->stepsLabel->TabIndex = 18;
			this->stepsLabel->Text = L"Steps back:";
			// 
			// frameLabel
			// 
			this->frameLabel->AutoSize = true;
			this->frameLabel->Location = System::Drawing::Point(116, 37);
			this->frameLabel->Name = L"frameLabel";
			this->frameLabel->Size = System::Drawing::Size(39, 13);
			this->frameLabel->TabIndex = 19;
			this->frameLabel->Text = L"Frame:";
			// 
			// zoomBox
			// 
			this->zoomBox->Location = System::Drawing::Point(187, 157);
			this->zoomBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->zoomBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->zoomBox->Name = L"zoomBox";
			this->zoomBox->Size = System::Drawing::Size(32, 20);
			this->zoomBox->TabIndex = 21;
			this->zoomBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// zoomLabel
			// 
			this->zoomLabel->AutoSize = true;
			this->zoomLabel->Location = System::Drawing::Point(98, 159);
			this->zoomLabel->Name = L"zoomLabel";
			this->zoomLabel->Size = System::Drawing::Size(83, 13);
			this->zoomLabel->TabIndex = 22;
			this->zoomLabel->Text = L"Draw one out of";
			// 
			// previewGroup
			// 
			this->previewGroup->Controls->Add(this->scaleMaxField);
			this->previewGroup->Controls->Add(this->normalizeCheckbox);
			this->previewGroup->Controls->Add(this->saveButton);
			this->previewGroup->Controls->Add(this->falseColorCheckbox);
			this->previewGroup->Controls->Add(this->zoomLabel2);
			this->previewGroup->Controls->Add(this->pixelSizeLabel);
			this->previewGroup->Controls->Add(this->pixelSizeBox);
			this->previewGroup->Controls->Add(this->zoomBox);
			this->previewGroup->Controls->Add(this->zoomLabel);
			this->previewGroup->Controls->Add(this->frameLabel);
			this->previewGroup->Controls->Add(this->frameListBox);
			this->previewGroup->Location = System::Drawing::Point(42, 533);
			this->previewGroup->Name = L"previewGroup";
			this->previewGroup->Size = System::Drawing::Size(280, 274);
			this->previewGroup->TabIndex = 23;
			this->previewGroup->TabStop = false;
			this->previewGroup->Text = L"Image Preview";
			// 
			// scaleMaxField
			// 
			this->scaleMaxField->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->scaleMaxField->Location = System::Drawing::Point(146, 254);
			this->scaleMaxField->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			this->scaleMaxField->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {255, 0, 0, 0});
			this->scaleMaxField->Name = L"scaleMaxField";
			this->scaleMaxField->Size = System::Drawing::Size(55, 20);
			this->scaleMaxField->TabIndex = 36;
			this->scaleMaxField->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {65535, 0, 0, 0});
			// 
			// normalizeCheckbox
			// 
			this->normalizeCheckbox->AutoSize = true;
			this->normalizeCheckbox->Location = System::Drawing::Point(22, 250);
			this->normalizeCheckbox->Name = L"normalizeCheckbox";
			this->normalizeCheckbox->Size = System::Drawing::Size(70, 17);
			this->normalizeCheckbox->TabIndex = 35;
			this->normalizeCheckbox->Text = L"normalize";
			this->normalizeCheckbox->UseVisualStyleBackColor = true;
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(140, 227);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(119, 23);
			this->saveButton->TabIndex = 26;
			this->saveButton->Text = L"Save Image Data";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &Form1::saveButton_Click);
			// 
			// falseColorCheckbox
			// 
			this->falseColorCheckbox->AutoSize = true;
			this->falseColorCheckbox->Location = System::Drawing::Point(22, 227);
			this->falseColorCheckbox->Name = L"falseColorCheckbox";
			this->falseColorCheckbox->Size = System::Drawing::Size(79, 17);
			this->falseColorCheckbox->TabIndex = 34;
			this->falseColorCheckbox->Text = L"false colors";
			this->falseColorCheckbox->UseVisualStyleBackColor = true;
			// 
			// zoomLabel2
			// 
			this->zoomLabel2->AutoSize = true;
			this->zoomLabel2->Location = System::Drawing::Point(225, 159);
			this->zoomLabel2->Name = L"zoomLabel2";
			this->zoomLabel2->Size = System::Drawing::Size(36, 13);
			this->zoomLabel2->TabIndex = 25;
			this->zoomLabel2->Text = L"pixels.";
			// 
			// pixelSizeLabel
			// 
			this->pixelSizeLabel->AutoSize = true;
			this->pixelSizeLabel->Location = System::Drawing::Point(100, 181);
			this->pixelSizeLabel->Name = L"pixelSizeLabel";
			this->pixelSizeLabel->Size = System::Drawing::Size(55, 13);
			this->pixelSizeLabel->TabIndex = 24;
			this->pixelSizeLabel->Text = L"Pixel Size:";
			// 
			// pixelSizeBox
			// 
			this->pixelSizeBox->Location = System::Drawing::Point(187, 178);
			this->pixelSizeBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {4, 0, 0, 0});
			this->pixelSizeBox->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->pixelSizeBox->Name = L"pixelSizeBox";
			this->pixelSizeBox->Size = System::Drawing::Size(32, 20);
			this->pixelSizeBox->TabIndex = 23;
			this->pixelSizeBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			// 
			// saveCheckBox
			// 
			this->saveCheckBox->AutoSize = true;
			this->saveCheckBox->Location = System::Drawing::Point(19, 38);
			this->saveCheckBox->Name = L"saveCheckBox";
			this->saveCheckBox->Size = System::Drawing::Size(51, 17);
			this->saveCheckBox->TabIndex = 25;
			this->saveCheckBox->Text = L"Save";
			this->saveCheckBox->UseVisualStyleBackColor = true;
			this->saveCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::saveCheckBox_CheckedChanged);
			// 
			// folderLabel
			// 
			this->folderLabel->AutoSize = true;
			this->folderLabel->Location = System::Drawing::Point(68, 13);
			this->folderLabel->Name = L"folderLabel";
			this->folderLabel->Size = System::Drawing::Size(347, 13);
			this->folderLabel->TabIndex = 26;
			this->folderLabel->TabStop = true;
			this->folderLabel->Text = L"C:\\Documents and Settings\\Lithium\\My Documents\\Online Fitting\\2012";
			this->folderLabel->Click += gcnew System::EventHandler(this, &Form1::pathClicked);
			// 
			// cameraLabel
			// 
			this->cameraLabel->AutoSize = true;
			this->cameraLabel->Location = System::Drawing::Point(58, 153);
			this->cameraLabel->Name = L"cameraLabel";
			this->cameraLabel->Size = System::Drawing::Size(73, 13);
			this->cameraLabel->TabIndex = 27;
			this->cameraLabel->Text = L"Camera Type:";
			// 
			// cameraListBox
			// 
			this->cameraListBox->FormattingEnabled = true;
			this->cameraListBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"No Camera", L"Sensicam", L"Princeton Instruments (WinView)", 
				L"Apogee"});
			this->cameraListBox->Location = System::Drawing::Point(59, 170);
			this->cameraListBox->Name = L"cameraListBox";
			this->cameraListBox->Size = System::Drawing::Size(242, 56);
			this->cameraListBox->TabIndex = 28;
			this->cameraListBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::cameraListBox_SelectedIndexChanged);
			// 
			// cameraNameLabel
			// 
			this->cameraNameLabel->AutoSize = true;
			this->cameraNameLabel->Location = System::Drawing::Point(137, 153);
			this->cameraNameLabel->Name = L"cameraNameLabel";
			this->cameraNameLabel->Size = System::Drawing::Size(53, 13);
			this->cameraNameLabel->TabIndex = 29;
			this->cameraNameLabel->Text = L"Sensicam";
			// 
			// singleFrameCheckBox
			// 
			this->singleFrameCheckBox->AutoSize = true;
			this->singleFrameCheckBox->Location = System::Drawing::Point(223, 246);
			this->singleFrameCheckBox->Name = L"singleFrameCheckBox";
			this->singleFrameCheckBox->Size = System::Drawing::Size(84, 17);
			this->singleFrameCheckBox->TabIndex = 30;
			this->singleFrameCheckBox->Text = L"Single frame";
			this->singleFrameCheckBox->UseVisualStyleBackColor = true;
			this->singleFrameCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::singleFrameCheckBox_CheckedChanged);
			// 
			// serverNameBox
			// 
			this->serverNameBox->Location = System::Drawing::Point(114, 824);
			this->serverNameBox->Name = L"serverNameBox";
			this->serverNameBox->Size = System::Drawing::Size(208, 20);
			this->serverNameBox->TabIndex = 31;
			this->serverNameBox->TextChanged += gcnew System::EventHandler(this, &Form1::serverNameBox_TextChanged);
			this->serverNameBox->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::serverNameBox_KeyUp);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(39, 831);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 13);
			this->label1->TabIndex = 32;
			this->label1->Text = L"Server Name";
			// 
			// currentServerNameLabel
			// 
			this->currentServerNameLabel->AutoSize = true;
			this->currentServerNameLabel->Location = System::Drawing::Point(111, 847);
			this->currentServerNameLabel->Name = L"currentServerNameLabel";
			this->currentServerNameLabel->Size = System::Drawing::Size(33, 13);
			this->currentServerNameLabel->TabIndex = 33;
			this->currentServerNameLabel->Text = L"name";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1259, 981);
			this->Controls->Add(this->currentServerNameLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->serverNameBox);
			this->Controls->Add(this->singleFrameCheckBox);
			this->Controls->Add(this->cameraNameLabel);
			this->Controls->Add(this->cameraListBox);
			this->Controls->Add(this->cameraLabel);
			this->Controls->Add(this->folderLabel);
			this->Controls->Add(this->saveCheckBox);
			this->Controls->Add(this->stepsLabel);
			this->Controls->Add(this->pictureBox);
			this->Controls->Add(this->prevListBox);
			this->Controls->Add(this->initButton);
			this->Controls->Add(this->formatListBox);
			this->Controls->Add(this->formatLabel);
			this->Controls->Add(this->saveLabel);
			this->Controls->Add(this->interruptButton);
			this->Controls->Add(this->imageProgressBar);
			this->Controls->Add(this->runIndicator);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->runButton);
			this->Controls->Add(this->layersLabel);
			this->Controls->Add(this->layersBox);
			this->Controls->Add(this->acquireButton);
			this->Controls->Add(this->camDialogButton);
			this->Controls->Add(this->previewGroup);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Simplicio SensiCam Controller";
			this->ResizeEnd += gcnew System::EventHandler(this, &Form1::Form1_ResizeEnd);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->layersBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->zoomBox))->EndInit();
			this->previewGroup->ResumeLayout(false);
			this->previewGroup->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->scaleMaxField))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pixelSizeBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public:
		void setLayersRead(int value);
		void loopFinished();
		void pictureBox_Paint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e );
		void addImageData(ImageData^ img);
		array<BufferedGraphics^>^ getEmptyBuffers(int numbuffers);
		void addBuffers(array<BufferedGraphics^>^ newbuffers, int numbuffers,ImageData^ img);
		void sequenceStarted(LinkedList<Variable^>^ listvars,  int iterNum);
		void setNextTime(DateTime nextTime);
		bool isSingleFrame();
		String^ getSaveFormat();
		bool isFalseColor();
		bool isNormalized();
		int getMaxScale();
		String^ getSavePath();
		void setServerName(String^ name);
		//BufferedGraphicsContext^ getContext(){return context;}
	private:
		static const int IMAGE_HISTORY_LENGTH = 20;
		static const int NUM_BUFFERS = 8;
		bool cameraInited;
		bool running;
		bool continueImageLoop;
		bool interruptImageLoop;
		String^ filePath;
		//UInt16 layers;
		//CameraSettings camSet;
		CameraThread^ camThread;
		ImageThread^ imgThread;
		SimplicioServer^ server;
		//Image^ previewImage;
		//ImageData^ imgData;
		array<int>^ layerHistory;//number of layers in each image
		array<ImageData^>^ imgDataArray;
		int imgDataIndex;//index to the most recently acquired image in imgDataArray
		int displayedImgInd;//index of the displayed image in steps back from imgDataIndex
		int displayedLayer;//the layer index of the displayed image (second index in buffers)
		void setSingleFrame(bool sf);
		//BufferedGraphics^ transmissionBuffer;
		//BufferedGraphics^ pwaBuffer;
		//BufferedGraphics^ pwoaBuffer;
		BufferedGraphicsContext^ context;
		BufferedGraphics^ imgBuffer;
		//array<BufferedGraphics^>^ bufferArray;
		array<array<BufferedGraphics^>^>^ buffers;
		//array<array<Bitmap^>^>^ bitmaps;
		//Bitmap^ imgBitmap;
		//LinkedList<Variable^>^ upcomingListVars;
	//stack of imgData:
		//Stack^ imgDataStack;
		void InitProgram();
		void EndProgram();
		void acquire(bool runLoop);
		void stopImageLoop();
		void interrupt(bool callback);
		bool openCameraDialog();
		void initCamera();
		void changeCamera();
	//	void takeImage(Object^ runloop);
	//	void saveImage(UInt16 rows, UInt16 cols, UInt16 lays, UInt16 *buf);
		void changePath();
		void setSaveFormat(String^ Format);
	//	void setProgressValue(int  value);
	//	void setProgressValueDirectly(int  value);
		void setDisplayImage(int stepsBack, int layer);
		void selectPreviousImage(int stepsBack);
		void setSaveData(bool savedata);
		int getHistoryIndex(int stepsBack);
		void saveImage(int stepsBack);
		void resize();
	//	void processNewImage(Object^ imgObj);
	//	void drawBuffers(int stepsBack);
		//listBoxNumers(int start,int stop);
		System::Void camDialogButton_Click(System::Object^  sender, System::EventArgs^  e){openCameraDialog();}
		System::Void acquireButton_Click(System::Object^  sender, System::EventArgs^  e){acquire(false);}
		System::Void runButton_Click(System::Object^  sender, System::EventArgs^  e){acquire(true);}
		System::Void stopButton_Click(System::Object^  sender, System::EventArgs^  e){stopImageLoop();}
		System::Void interruptButton_Click(System::Object^  sender, System::EventArgs^  e){interrupt(true);}
		System::Void pathClicked(System::Object^  sender, System::EventArgs^  e){changePath();}
		System::Void initButton_Click(System::Object^  sender, System::EventArgs^  e) {initCamera();}
		System::Void prevListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
		{
			selectPreviousImage(prevListBox->SelectedIndex);
		}
		System::Void frameListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) 
		{
			setDisplayImage(prevListBox->SelectedIndex,frameListBox->SelectedIndex);
		}
		System::Void saveCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {setSaveData(saveCheckBox->Checked);}
		System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) {saveImage(prevListBox->SelectedIndex);}
		System::Void Form1_ResizeEnd(System::Object^  sender, System::EventArgs^  e) {resize();}
private: System::Void folderBrowserDialog_HelpRequest(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void pathLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
		 }


private: System::Void cameraListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 //MessageBox::Show(String::Concat("Changing camera. ",e->GetType()->ToString()),"Simplicio",MessageBoxButtons::OK);
			 changeCamera();
			 
		 }
private: System::Void singleFrameCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			setSingleFrame(singleFrameCheckBox->Checked);
		 }
private: System::Void serverNameBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			// setServerName(serverNameBox->Text);
		 }
private: System::Void serverNameBox_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if (e->KeyCode == Keys::Enter){
				setServerName(serverNameBox->Text);
			}
		 }

private: System::Void formatListBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 setSaveFormat(getSaveFormat());
		 }
};
}


#pragma once
#pragma comment (lib, "User32.lib")
#include <ctime>
#include <cstdint>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <chrono>
#include <thread>
#include <string>
#include <msclr\marshal.h>

namespace DrillClickRecorder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Diagnostics;
	using namespace System::Drawing;
	using namespace msclr::interop;

	public ref class ClickRecorder : public System::Windows::Forms::Form
	{
	public:
		ClickRecorder(void)
		{
			InitializeComponent();
		}

#pragma region Garbage Collection
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClickRecorder()
		{
			if (components)
			{
				delete components;
			}
		}
#pragma endregion

#pragma region Variables
	private:
		unsigned short cps = 10;
		HWND mc;
		bool worksInMenus = false;
#pragma endregion

#pragma region Methods
		HWND FindMc() {
			marshal_context context;
			return FindWindow(NULL, context.marshal_as<const TCHAR*>(Process::GetProcessesByName("javaw")[0]->MainWindowTitle));
		}
#pragma endregion

#pragma region Controls
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Timer^ timer2;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ CpsLabel;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ button2;
#pragma endregion

#pragma region Event Handlers
	private: System::Void ClickRecorder_Load(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void ToggleClicker(System::Object^ sender, System::EventArgs^ e) {
		if (button1->Text->ToString()->Contains("Enable")) {
			button1->Text = "Disable";
			timer1->Start();
		}
		else {
			button1->Text = "Enable";
			timer1->Stop();
		}
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		timer1->Interval = 1000 / (cps - 2 + rand() % 6);

		mc = FindMc();

		CURSORINFO ci = { sizeof(CURSORINFO) };
		GetCursorInfo(&ci);

		if (GetAsyncKeyState(0x01) != 0
			&& GetForegroundWindow() == mc
			&& ((int)ci.hCursor > 100000 || worksInMenus))
		{
			PostMessage(mc, 0x201, 0, 0);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			PostMessage(mc, 0x202, 0, 0);
		}
	}

	private: System::Void timer2_Tick(System::Object ^ sender, System::EventArgs ^ e) {
	}

	private: System::Void ToggleWorksInMenu(System::Object^ sender, System::EventArgs^ e) {
		worksInMenus = !worksInMenus;
	}

	private: System::Void CpsChanged(System::Object^ sender, System::EventArgs^ e) {
		cps = trackBar1->Value;
		CpsLabel->Text = cps.ToString();
	}
#pragma endregion

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			   this->CpsLabel = (gcnew System::Windows::Forms::Label());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->timer2 = (gcnew System::Windows::Forms::Timer(this->components));
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(4, 18);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(28, 13);
			   this->label1->TabIndex = 0;
			   this->label1->Text = L"CPS";
			   // 
			   // button1
			   // 
			   this->button1->Location = System::Drawing::Point(7, 226);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(75, 23);
			   this->button1->TabIndex = 1;
			   this->button1->Text = L"Enable";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &ClickRecorder::ToggleClicker);
			   // 
			   // trackBar1
			   // 
			   this->trackBar1->Location = System::Drawing::Point(38, 12);
			   this->trackBar1->Maximum = 20;
			   this->trackBar1->Minimum = 10;
			   this->trackBar1->Name = L"trackBar1";
			   this->trackBar1->Size = System::Drawing::Size(234, 45);
			   this->trackBar1->TabIndex = 2;
			   this->trackBar1->TickStyle = System::Windows::Forms::TickStyle::None;
			   this->trackBar1->Value = 10;
			   this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &ClickRecorder::CpsChanged);
			   // 
			   // CpsLabel
			   // 
			   this->CpsLabel->AutoSize = true;
			   this->CpsLabel->Location = System::Drawing::Point(137, 31);
			   this->CpsLabel->Name = L"CpsLabel";
			   this->CpsLabel->Size = System::Drawing::Size(19, 13);
			   this->CpsLabel->TabIndex = 3;
			   this->CpsLabel->Text = L"10";
			   // 
			   // timer1
			   // 
			   this->timer1->Tick += gcnew System::EventHandler(this, &ClickRecorder::timer1_Tick);
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Location = System::Drawing::Point(7, 58);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(58, 17);
			   this->checkBox1->TabIndex = 4;
			   this->checkBox1->Text = L"Menus";
			   this->checkBox1->UseVisualStyleBackColor = true;
			   this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &ClickRecorder::ToggleWorksInMenu);
			   // 
			   // button2
			   // 
			   this->button2->Location = System::Drawing::Point(88, 226);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(30, 23);
			   this->button2->TabIndex = 5;
			   this->button2->Text = L"...";
			   this->button2->UseVisualStyleBackColor = true;
			   // 
			   // ClickRecorder
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->AutoSize = true;
			   this->ClientSize = System::Drawing::Size(284, 261);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->checkBox1);
			   this->Controls->Add(this->CpsLabel);
			   this->Controls->Add(this->trackBar1);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->label1);
			   this->Location = System::Drawing::Point(7, 236);
			   this->MaximizeBox = false;
			   this->Name = L"ClickRecorder";
			   this->Text = L"ClickRecorder";
			   this->Load += gcnew System::EventHandler(this, &ClickRecorder::ClickRecorder_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	};
}

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

namespace DrillClickRecorder {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Diagnostics;
	using namespace System::Drawing;

	public ref class ClickRecorder : public System::Windows::Forms::Form
	{
	public:
		ClickRecorder(void)
		{
			InitializeComponent();

		}

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

	private:
		#pragma region Variables
		HWND mc;
		#pragma endregion

		#pragma region Methods
		HWND FindMc() {
			return FindWindow(NULL, L"Minecraft 1.7.10");
		}
		#pragma endregion

		#pragma region Controls
		private: System::ComponentModel::IContainer^ components;
		private: System::Windows::Forms::Timer^ timer1;
		private: System::Windows::Forms::Label^ label2;
		private: System::Windows::Forms::Button^ button1;
		#pragma endregion

		#pragma region Event Handlers
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
			mc = FindMc();
			if (GetAsyncKeyState(0x01) != 0 && GetForegroundWindow() == mc)
			{
				PostMessage(mc, 0x201, 0, 0);
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				PostMessage(mc, 0x202, 0, 0);
			}
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
			System::Windows::Forms::Label^ label1;
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(4, 4);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(28, 13);
			label1->TabIndex = 0;
			label1->Text = L"CPS";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(7, 21);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Enable";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ClickRecorder::ToggleClicker);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ClickRecorder::timer1_Tick);
			// 
			// ClickRecorder
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->button1);
			this->Controls->Add(label1);
			this->Location = System::Drawing::Point(7, 236);
			this->Name = L"ClickRecorder";
			this->Text = L"ClickRecorder";
			this->Load += gcnew System::EventHandler(this, &ClickRecorder::ClickRecorder_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ClickRecorder_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}

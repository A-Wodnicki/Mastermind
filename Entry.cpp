#include "Entry.h"

Mastermind::Entry::Entry() {
	InitializeComponent();
}

Mastermind::Entry::~Entry() {
	if (components) {
		delete components;
	}
}

System::Void Mastermind::Entry::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	Mastermind::Login^ login = gcnew Mastermind::Login;
}

System::Void Mastermind::Entry::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	Mastermind::Register^ register_window = gcnew Mastermind::Register;
}

System::Void Mastermind::Entry::InitializeComponent(void) {
	this->button1 = (gcnew System::Windows::Forms::Button());
	this->button2 = (gcnew System::Windows::Forms::Button());
	this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
	this->flowLayoutPanel1->SuspendLayout();
	this->SuspendLayout();
	// 
	// button1
	// 
	this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
		| System::Windows::Forms::AnchorStyles::Right));
	this->button1->AutoSize = true;
	this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->button1->BackColor = System::Drawing::SystemColors::Control;
	this->button1->ImeMode = System::Windows::Forms::ImeMode::NoControl;
	this->button1->Location = System::Drawing::Point(0, 0);
	this->button1->Margin = System::Windows::Forms::Padding(0, 0, 0, 16);
	this->button1->Name = L"button1";
	this->button1->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
	this->button1->Size = System::Drawing::Size(142, 55);
	this->button1->TabIndex = 0;
	this->button1->Text = L"Login";
	this->button1->UseMnemonic = false;
	this->button1->UseVisualStyleBackColor = true;
	this->button1->Click += gcnew System::EventHandler(this, &Entry::button1_Click);
	// 
	// button2
	// 
	this->button2->AutoSize = true;
	this->button2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->button2->Location = System::Drawing::Point(0, 71);
	this->button2->Margin = System::Windows::Forms::Padding(0);
	this->button2->Name = L"button2";
	this->button2->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
	this->button2->Size = System::Drawing::Size(142, 55);
	this->button2->TabIndex = 1;
	this->button2->Text = L"Register";
	this->button2->UseVisualStyleBackColor = true;
	this->button2->Click += gcnew System::EventHandler(this, &Entry::button2_Click);
	// 
	// flowLayoutPanel1
	// 
	this->flowLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
		| System::Windows::Forms::AnchorStyles::Right));
	this->flowLayoutPanel1->AutoSize = true;
	this->flowLayoutPanel1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
	this->flowLayoutPanel1->Controls->Add(this->button1);
	this->flowLayoutPanel1->Controls->Add(this->button2);
	this->flowLayoutPanel1->FlowDirection = System::Windows::Forms::FlowDirection::TopDown;
	this->flowLayoutPanel1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F));
	this->flowLayoutPanel1->ForeColor = System::Drawing::SystemColors::ControlText;
	this->flowLayoutPanel1->Location = System::Drawing::Point(329, 237);
	this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
	this->flowLayoutPanel1->Size = System::Drawing::Size(142, 126);
	this->flowLayoutPanel1->TabIndex = 2;
	// 
	// Entry
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(780, 557);
	this->Controls->Add(this->flowLayoutPanel1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
	this->MaximizeBox = false;
	this->Name = L"Entry";
	this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
	this->Text = L"Entry";
	this->flowLayoutPanel1->ResumeLayout(false);
	this->flowLayoutPanel1->PerformLayout();
	this->ResumeLayout(false);
	this->PerformLayout();
}

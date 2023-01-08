#include "Register.h"

Mastermind::Register::Register() {
    InitializeComponent();
    this->ShowDialog();
}

Mastermind::Register::~Register() {
    if (components) {
        delete components;
    }
}

void Mastermind::Register::InitializeComponent(void) {
    this->SuspendLayout();
    // 
    // Register
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(780, 557);
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
    this->MaximizeBox = false;
    this->Name = L"Register";
    this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Register";
    this->ResumeLayout(false);

}
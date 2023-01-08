#include "Login.h"

Mastermind::Login::Login() {
  InitializeComponent();
  this->ShowDialog();
}

Mastermind::Login::~Login() {
  if (components) {
    delete components;
  }
}

void Mastermind::Login::InitializeComponent(void) {
    this->SuspendLayout();
    // 
    // Login
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = System::Drawing::Size(780, 557);
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
    this->MaximizeBox = false;
    this->Name = L"Login";
    this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Login";
    this->ResumeLayout(false);

}
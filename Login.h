#pragma once

namespace Mastermind {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  /// <summary>
  /// Summary for Login
  /// </summary>
  public ref class Login : public System::Windows::Forms::Form
  {
  public:
    static bool open = false;
    Login(void)
    {
      InitializeComponent();      
      //
      //TODO: Add the constructor code here
      //
    }
  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~Login()
    {
      if (components)
      {
        delete components;
      }
      open = false;
    }
  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->SuspendLayout();
      // 
      // Login
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(784, 561);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
      this->MaximizeBox = false;
      this->Name = L"Login";
      this->Text = L"Login";
      this->Load += gcnew System::EventHandler(this, &Login::Login_Load);
      this->ResumeLayout(false);

    }
#pragma endregion
  private: System::Void Login_Load(System::Object^ sender, System::EventArgs^ e) {
    open = true;
  }
  };
}

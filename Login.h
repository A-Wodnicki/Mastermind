#pragma once

namespace Mastermind {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class Login : public System::Windows::Forms::Form {
  public:
    Login();
  protected:
    ~Login();
  private:
    System::ComponentModel::Container^ components;
    void InitializeComponent();    
  };
}

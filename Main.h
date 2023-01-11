#include "Login.h"
#include "Register.h"

#pragma once

namespace Mastermind {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class Main : public System::Windows::Forms::Form {
  public:
    Main();
  protected:
    ~Main();
  private:
    Mastermind::Register^ register_window = gcnew Mastermind::Register;
    Mastermind::Login^ login_window = gcnew Mastermind::Login;
    System::Windows::Forms::Button^ open_login_button;
    System::Windows::Forms::Button^ open_register_button;
    System::Windows::Forms::Button^ open_history_button;
    System::Windows::Forms::Button^ open_settings_button;
    System::Windows::Forms::Button^ quit_button;
    System::Windows::Forms::TableLayoutPanel^ main_menu_buttons;
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
    System::ComponentModel::Container^ components;
    System::Void open_login_button_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void open_register_button_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void InitializeComponent();
    System::Void quit_button_Click(System::Object^ sender, System::EventArgs^ e);
  };
}

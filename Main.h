#include "Login.h"
#include "Register.h"
#include "Game.h"
#include "Stats.h"
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
    System::String^ username;
    Mastermind::Register^ register_window = gcnew Mastermind::Register;
    Mastermind::Login^ login_window = gcnew Mastermind::Login;
    Mastermind::Game^ game_window = gcnew Mastermind::Game;
    Mastermind::Stats^ stats_window = gcnew Mastermind::Stats;
    System::Windows::Forms::Button^ open_login_button;
    System::Windows::Forms::Button^ open_register_button;
  private: System::Windows::Forms::Button^ open_stats_button;


    System::Windows::Forms::Button^ quit_button;
    System::Windows::Forms::TableLayoutPanel^ main_menu_buttons;
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
    System::ComponentModel::Container^ components;
    System::Void open_login_button_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void open_register_button_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void InitializeComponent();
    System::Void quit_button_Click(System::Object^ sender, System::EventArgs^ e);
    System::Void open_stats_button_Click(System::Object^ sender, System::EventArgs^ e);
  };
}

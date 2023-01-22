#pragma once

namespace Mastermind {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class Register : public System::Windows::Forms::Form {
  public:
    Register();
    bool user_created;
    System::String^ username;
  protected:
    ~Register();
  private:
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
    System::Windows::Forms::TableLayoutPanel^ register_form;
    System::Windows::Forms::Label^ username_label;
    System::Windows::Forms::Label^ password_label;
    System::Windows::Forms::Label^ confirm_password_label;
    System::Windows::Forms::Button^ register_button;
    System::Windows::Forms::Button^ cancel_button;
    System::Windows::Forms::TextBox^ username_input;
    System::Windows::Forms::TextBox^ password_input;
    System::Windows::Forms::TextBox^ confirm_password_input;
    System::ComponentModel::Container^ components;
    void InitializeComponent();
    System::Void register_button_Click(System::Object^ sender, System::EventArgs^ e);
  };
}

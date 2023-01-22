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
    bool user_verified;
    System::String^ username;
  protected:
    ~Login();
  private:
    System::Windows::Forms::TextBox^ textBox1;
    System::Windows::Forms::TextBox^ textBox2;
    System::Windows::Forms::Label^ label1;
    System::Windows::Forms::Label^ label2;
    System::Windows::Forms::Button^ button1;
    System::Windows::Forms::Button^ button2;
    System::Windows::Forms::FlowLayoutPanel^ buttons;
    System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel5;
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
    System::Windows::Forms::TableLayoutPanel^ login_form;
    System::Windows::Forms::Button^ login_button;
    System::Windows::Forms::Button^ cancel_button;
    System::Windows::Forms::Label^ username_label;
    System::Windows::Forms::Label^ password_label;
    System::Windows::Forms::TextBox^ username_input;
    System::Windows::Forms::TextBox^ password_input;
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
    System::Data::DataSet^ dataSet1;
    System::ComponentModel::IContainer^ components;
    void InitializeComponent();
    System::Void login_button_Click(System::Object^ sender, System::EventArgs^ e);
  
  };
}

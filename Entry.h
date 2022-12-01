#include "Login.h"

#pragma once

namespace Mastermind {
  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class Entry : public System::Windows::Forms::Form {
  public:
    Entry();
  protected:
    ~Entry();
  private:
    Int32^ window_width,window_height;
    System::Windows::Forms::Button^ button1;
    System::Windows::Forms::Button^ button2;
    System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
    System::ComponentModel::Container^ components;
    System::Void InitializeComponent();
    System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
  };
}

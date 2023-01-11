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
  protected:
    ~Register();
  private:
    System::ComponentModel::Container^ components;
    void InitializeComponent();
  };
}

#pragma once

namespace Mastermind {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::Data::SqlClient;
  using namespace System::Data::Odbc;

  public ref class Stats : public System::Windows::Forms::Form {
  public:
    Stats(void);
  protected:
    ~Stats();
  private:
    System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
    System::Windows::Forms::BindingSource^ bindingSource1;
    System::Data::DataSet^ dataSet1;
    System::Windows::Forms::DataGridView^ dataGridView1;
    System::Windows::Forms::Button^ button1;
    System::ComponentModel::IContainer^ components;
    void InitializeComponent(void);
    System::Void Stats_Load(System::Object^ sender, System::EventArgs^ e);
    System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
  };
}

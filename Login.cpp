#include "Login.h"
#include "Error.h"

Mastermind::Login::Login() {
  InitializeComponent();
  user_verified = false;
}

Mastermind::Login::~Login() {
  if (components) {
    delete components;
  }
}

void Mastermind::Login::InitializeComponent(void) {
  this->login_form = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->login_button = (gcnew System::Windows::Forms::Button());
  this->username_label = (gcnew System::Windows::Forms::Label());
  this->username_input = (gcnew System::Windows::Forms::TextBox());
  this->password_input = (gcnew System::Windows::Forms::TextBox());
  this->password_label = (gcnew System::Windows::Forms::Label());
  this->cancel_button = (gcnew System::Windows::Forms::Button());
  this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->dataSet1 = (gcnew System::Data::DataSet());
  this->login_form->SuspendLayout();
  this->tableLayoutPanel3->SuspendLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
  this->SuspendLayout();
  // 
  // login_form
  // 
  this->login_form->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->login_form->AutoSize = true;
  this->login_form->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->login_form->ColumnCount = 2;
  this->login_form->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->login_form->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->login_form->Controls->Add(this->login_button, 0, 2);
  this->login_form->Controls->Add(this->username_label, 0, 0);
  this->login_form->Controls->Add(this->username_input, 1, 0);
  this->login_form->Controls->Add(this->password_input, 1, 1);
  this->login_form->Controls->Add(this->password_label, 0, 1);
  this->login_form->Controls->Add(this->cancel_button, 1, 2);
  this->login_form->Location = System::Drawing::Point(255, 222);
  this->login_form->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
  this->login_form->Name = L"login_form";
  this->login_form->RowCount = 3;
  this->login_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->login_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->login_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->login_form->Size = System::Drawing::Size(290, 156);
  this->login_form->TabIndex = 0;
  // 
  // login_button
  // 
  this->login_button->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->login_button->AutoSize = true;
  this->login_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->login_button->Location = System::Drawing::Point(8, 96);
  this->login_button->Margin = System::Windows::Forms::Padding(8);
  this->login_button->Name = L"login_button";
  this->login_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->login_button->Size = System::Drawing::Size(104, 52);
  this->login_button->TabIndex = 0;
  this->login_button->Text = L"Login";
  this->login_button->UseVisualStyleBackColor = true;
  this->login_button->Click += gcnew System::EventHandler(this, &Login::login_button_Click);
  // 
  // username_label
  // 
  this->username_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
  this->username_label->AutoSize = true;
  this->username_label->Location = System::Drawing::Point(15, 11);
  this->username_label->Margin = System::Windows::Forms::Padding(8);
  this->username_label->Name = L"username_label";
  this->username_label->Size = System::Drawing::Size(97, 22);
  this->username_label->TabIndex = 2;
  this->username_label->Text = L"Username:";
  // 
  // username_input
  // 
  this->username_input->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
  this->username_input->Location = System::Drawing::Point(128, 8);
  this->username_input->Margin = System::Windows::Forms::Padding(8);
  this->username_input->Name = L"username_input";
  this->username_input->Size = System::Drawing::Size(154, 28);
  this->username_input->TabIndex = 4;
  // 
  // password_input
  // 
  this->password_input->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
  this->password_input->Location = System::Drawing::Point(128, 52);
  this->password_input->Margin = System::Windows::Forms::Padding(8);
  this->password_input->Name = L"password_input";
  this->password_input->PasswordChar = '*';
  this->password_input->Size = System::Drawing::Size(154, 28);
  this->password_input->TabIndex = 5;
  // 
  // password_label
  // 
  this->password_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
  this->password_label->AutoSize = true;
  this->password_label->Location = System::Drawing::Point(18, 55);
  this->password_label->Margin = System::Windows::Forms::Padding(8);
  this->password_label->Name = L"password_label";
  this->password_label->Size = System::Drawing::Size(94, 22);
  this->password_label->TabIndex = 3;
  this->password_label->Text = L"Password:";
  // 
  // cancel_button
  // 
  this->cancel_button->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->cancel_button->AutoSize = true;
  this->cancel_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->cancel_button->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  this->cancel_button->Location = System::Drawing::Point(147, 96);
  this->cancel_button->Margin = System::Windows::Forms::Padding(8);
  this->cancel_button->Name = L"cancel_button";
  this->cancel_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->cancel_button->Size = System::Drawing::Size(116, 52);
  this->cancel_button->TabIndex = 1;
  this->cancel_button->Text = L"Cancel";
  this->cancel_button->UseVisualStyleBackColor = true;
  // 
  // tableLayoutPanel3
  // 
  this->tableLayoutPanel3->ColumnCount = 1;
  this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel3->Controls->Add(this->login_form, 0, 0);
  this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
  this->tableLayoutPanel3->Location = System::Drawing::Point(0, 0);
  this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(8);
  this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
  this->tableLayoutPanel3->RowCount = 1;
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->Size = System::Drawing::Size(800, 600);
  this->tableLayoutPanel3->TabIndex = 1;
  // 
  // dataSet1
  // 
  this->dataSet1->DataSetName = L"NewDataSet";
  // 
  // Login
  // 
  this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
  this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
  this->ClientSize = System::Drawing::Size(800, 600);
  this->Controls->Add(this->tableLayoutPanel3);
  this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel,
    static_cast<System::Byte>(238)));
  this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
  this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
  this->MinimumSize = System::Drawing::Size(800, 600);
  this->Name = L"Login";
  this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
  this->Text = L"Mastermind";
  this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
  this->login_form->ResumeLayout(false);
  this->login_form->PerformLayout();
  this->tableLayoutPanel3->ResumeLayout(false);
  this->tableLayoutPanel3->PerformLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
  this->ResumeLayout(false);

}

System::Void Mastermind::Login::login_button_Click(System::Object^ sender, System::EventArgs^ e)
{
  user_verified = false;
  System::Data::SqlClient::SqlConnection^ conDatabase = gcnew System::Data::SqlClient::SqlConnection("Data Source=localhost\\SQLEXPRESS;Initial Catalog=mastermind;Integrated Security=SSPI");
  String^ query = "SELECT username, password FROM users WHERE username = '" + this->username_input->Text + "' AND password = HASHBYTES('SHA2_512', '" + this->password_input->Text + "')";
  System::Data::SqlClient::SqlCommand^ cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
  System::Data::SqlClient::SqlDataAdapter^ sda = gcnew System::Data::SqlClient::SqlDataAdapter();
  sda->SelectCommand = cmd;
  dataSet1->Reset();
  try {
    sda->Fill(dataSet1);
  }
  catch (System::Data::SqlClient::SqlException^) {
    (gcnew Error(1, "Unable to get connection to database"))->Describe();
    return;
  }
  try {
    if (!dataSet1->Tables[0]->Rows->Count) {
      throw gcnew Error(2, "The user with the given name and password was not found");
    }
  }
  catch (Error^ err) {
    err->Describe();
      return;
  }
  user_verified = true;
  username = username_input->Text;
  Close();
}



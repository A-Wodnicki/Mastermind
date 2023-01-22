#include "Register.h"
#include "Error.h"

Mastermind::Register::Register() {
  InitializeComponent();
  user_created = false;
}

Mastermind::Register::~Register() {
  if (components) {
    delete components;
  }
}

void Mastermind::Register::InitializeComponent(void) {
  this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->register_form = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->username_label = (gcnew System::Windows::Forms::Label());
  this->password_label = (gcnew System::Windows::Forms::Label());
  this->confirm_password_label = (gcnew System::Windows::Forms::Label());
  this->cancel_button = (gcnew System::Windows::Forms::Button());
  this->username_input = (gcnew System::Windows::Forms::TextBox());
  this->password_input = (gcnew System::Windows::Forms::TextBox());
  this->confirm_password_input = (gcnew System::Windows::Forms::TextBox());
  this->register_button = (gcnew System::Windows::Forms::Button());
  this->tableLayoutPanel1->SuspendLayout();
  this->register_form->SuspendLayout();
  this->SuspendLayout();
  // 
  // tableLayoutPanel1
  // 
  this->tableLayoutPanel1->ColumnCount = 1;
  this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    50)));
  this->tableLayoutPanel1->Controls->Add(this->register_form, 0, 0);
  this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
  this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
  this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
  this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
  this->tableLayoutPanel1->RowCount = 1;
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
  this->tableLayoutPanel1->Size = System::Drawing::Size(800, 599);
  this->tableLayoutPanel1->TabIndex = 0;
  // 
  // register_form
  // 
  this->register_form->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->register_form->AutoSize = true;
  this->register_form->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->register_form->ColumnCount = 2;
  this->register_form->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->register_form->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->register_form->Controls->Add(this->username_label, 0, 0);
  this->register_form->Controls->Add(this->password_label, 0, 1);
  this->register_form->Controls->Add(this->confirm_password_label, 0, 2);
  this->register_form->Controls->Add(this->cancel_button, 1, 3);
  this->register_form->Controls->Add(this->username_input, 1, 0);
  this->register_form->Controls->Add(this->password_input, 1, 1);
  this->register_form->Controls->Add(this->confirm_password_input, 1, 2);
  this->register_form->Controls->Add(this->register_button, 0, 3);
  this->register_form->Location = System::Drawing::Point(227, 199);
  this->register_form->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
  this->register_form->Name = L"register_form";
  this->register_form->RowCount = 4;
  this->register_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->register_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->register_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->register_form->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->register_form->Size = System::Drawing::Size(345, 200);
  this->register_form->TabIndex = 0;
  // 
  // username_label
  // 
  this->username_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
  this->username_label->AutoSize = true;
  this->username_label->Location = System::Drawing::Point(70, 11);
  this->username_label->Margin = System::Windows::Forms::Padding(8);
  this->username_label->Name = L"username_label";
  this->username_label->Size = System::Drawing::Size(97, 22);
  this->username_label->TabIndex = 0;
  this->username_label->Text = L"Username:";
  // 
  // password_label
  // 
  this->password_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
  this->password_label->AutoSize = true;
  this->password_label->Location = System::Drawing::Point(73, 55);
  this->password_label->Margin = System::Windows::Forms::Padding(8);
  this->password_label->Name = L"password_label";
  this->password_label->Size = System::Drawing::Size(94, 22);
  this->password_label->TabIndex = 1;
  this->password_label->Text = L"Password:";
  // 
  // confirm_password_label
  // 
  this->confirm_password_label->Anchor = System::Windows::Forms::AnchorStyles::Right;
  this->confirm_password_label->AutoSize = true;
  this->confirm_password_label->Location = System::Drawing::Point(8, 99);
  this->confirm_password_label->Margin = System::Windows::Forms::Padding(8);
  this->confirm_password_label->Name = L"confirm_password_label";
  this->confirm_password_label->Size = System::Drawing::Size(159, 22);
  this->confirm_password_label->TabIndex = 2;
  this->confirm_password_label->Text = L"Confirm password:";
  // 
  // cancel_button
  // 
  this->cancel_button->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->cancel_button->AutoSize = true;
  this->cancel_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->cancel_button->DialogResult = System::Windows::Forms::DialogResult::Cancel;
  this->cancel_button->Location = System::Drawing::Point(202, 140);
  this->cancel_button->Margin = System::Windows::Forms::Padding(8);
  this->cancel_button->Name = L"cancel_button";
  this->cancel_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->cancel_button->Size = System::Drawing::Size(116, 52);
  this->cancel_button->TabIndex = 4;
  this->cancel_button->Text = L"Cancel";
  this->cancel_button->UseVisualStyleBackColor = true;
  // 
  // username_input
  // 
  this->username_input->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
  this->username_input->Location = System::Drawing::Point(183, 8);
  this->username_input->Margin = System::Windows::Forms::Padding(8);
  this->username_input->Name = L"username_input";
  this->username_input->Size = System::Drawing::Size(154, 28);
  this->username_input->TabIndex = 5;
  // 
  // password_input
  // 
  this->password_input->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
  this->password_input->Location = System::Drawing::Point(183, 52);
  this->password_input->Margin = System::Windows::Forms::Padding(8);
  this->password_input->Name = L"password_input";
  this->password_input->PasswordChar = '*';
  this->password_input->Size = System::Drawing::Size(154, 28);
  this->password_input->TabIndex = 6;
  // 
  // confirm_password_input
  // 
  this->confirm_password_input->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
  this->confirm_password_input->Location = System::Drawing::Point(183, 96);
  this->confirm_password_input->Margin = System::Windows::Forms::Padding(8);
  this->confirm_password_input->Name = L"confirm_password_input";
  this->confirm_password_input->PasswordChar = '*';
  this->confirm_password_input->Size = System::Drawing::Size(154, 28);
  this->confirm_password_input->TabIndex = 7;
  // 
  // register_button
  // 
  this->register_button->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->register_button->AutoSize = true;
  this->register_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->register_button->Location = System::Drawing::Point(24, 140);
  this->register_button->Margin = System::Windows::Forms::Padding(8);
  this->register_button->Name = L"register_button";
  this->register_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->register_button->Size = System::Drawing::Size(127, 52);
  this->register_button->TabIndex = 3;
  this->register_button->Text = L"Register";
  this->register_button->UseVisualStyleBackColor = true;
  this->register_button->Click += gcnew System::EventHandler(this, &Register::register_button_Click);
  // 
  // Register
  // 
  this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
  this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
  this->ClientSize = System::Drawing::Size(784, 560);
  this->Controls->Add(this->tableLayoutPanel1);
  this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel,
    static_cast<System::Byte>(238)));
  this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
  this->Margin = System::Windows::Forms::Padding(2, 3, 2, 3);
  this->MinimumSize = System::Drawing::Size(800, 599);
  this->Name = L"Register";
  this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
  this->Text = L"Mastermind";
  this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
  this->tableLayoutPanel1->ResumeLayout(false);
  this->tableLayoutPanel1->PerformLayout();
  this->register_form->ResumeLayout(false);
  this->register_form->PerformLayout();
  this->ResumeLayout(false);

}

System::Void Mastermind::Register::register_button_Click(System::Object^ sender, System::EventArgs^ e)
{
  this->username = this->username_input->Text;
  user_created = false;
  try {
    if (password_input->Text != confirm_password_input->Text) {
      throw gcnew Error(4, "Has³a nie s¹ takie same");
    }
  }
  catch (Error^ e) {
    e->Describe();
    return;
  }
  System::Data::SqlClient::SqlConnection^ conDatabase = gcnew System::Data::SqlClient::SqlConnection("Data Source=localhost\\SQLEXPRESS;Initial Catalog=mastermind;Integrated Security=SSPI");
  try {
    conDatabase->Open();
  }
  catch (SqlClient::SqlException^) {
    (gcnew Error(1, "Nie mo¿na uzyskaæ po³¹czenia z baz¹ danych"))->Describe();
    return;
  }
  String^ query = "INSERT INTO users VALUES('" + this->username + "', HASHBYTES('SHA2_512', '" + this->password_input->Text + "'))";
  System::Data::SqlClient::SqlCommand^ cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
  try {
    cmd->ExecuteNonQuery();
  }
  catch (SqlClient::SqlException^) {
    (gcnew Error(3, "U¿ytkownik o podanej nazwie ju¿ istnieje"))->Describe();
    return;
  }
  query = "INSERT INTO [stats] VALUES((SELECT id from users WHERE username='" + this->username + "'), 0, 0, NULL)";
  cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
  cmd->ExecuteNonQuery();
  delete cmd;
  conDatabase->Close();
  delete conDatabase;
  user_created = true;
  Close();
}

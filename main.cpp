#include "Main.h"

Mastermind::Main::Main() {
  InitializeComponent();
}

Mastermind::Main::~Main() {
  if (components) {
    delete components;
  }
}

System::Void Mastermind::Main::open_login_button_Click(System::Object^ sender, System::EventArgs^ e) {
  this->login_window->ShowDialog();
  if (this->login_window->user_verified) {
    this->game_window->ShowDialog();
  }
}

System::Void Mastermind::Main::open_register_button_Click(System::Object^ sender, System::EventArgs^ e) {
  this->register_window->ShowDialog();
  if (this->register_window->user_created) {
    this->game_window->ShowDialog();
  }
}

System::Void Mastermind::Main::InitializeComponent(void) {
    this->open_login_button = (gcnew System::Windows::Forms::Button());
    this->open_register_button = (gcnew System::Windows::Forms::Button());
    this->open_history_button = (gcnew System::Windows::Forms::Button());
    this->open_settings_button = (gcnew System::Windows::Forms::Button());
    this->quit_button = (gcnew System::Windows::Forms::Button());
    this->main_menu_buttons = (gcnew System::Windows::Forms::TableLayoutPanel());
    this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
    this->main_menu_buttons->SuspendLayout();
    this->tableLayoutPanel2->SuspendLayout();
    this->SuspendLayout();
    // 
    // open_login_button
    // 
    this->open_login_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
    this->open_login_button->AutoSize = true;
    this->open_login_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->open_login_button->BackColor = System::Drawing::SystemColors::Control;
    this->open_login_button->ImeMode = System::Windows::Forms::ImeMode::NoControl;
    this->open_login_button->Location = System::Drawing::Point(8, 8);
    this->open_login_button->Margin = System::Windows::Forms::Padding(8);
    this->open_login_button->Name = L"open_login_button";
    this->open_login_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
    this->open_login_button->Size = System::Drawing::Size(181, 52);
    this->open_login_button->TabIndex = 0;
    this->open_login_button->Text = L"Login";
    this->open_login_button->UseMnemonic = false;
    this->open_login_button->UseVisualStyleBackColor = true;
    this->open_login_button->Click += gcnew System::EventHandler(this, &Main::open_login_button_Click);
    // 
    // open_register_button
    // 
    this->open_register_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
    this->open_register_button->AutoSize = true;
    this->open_register_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->open_register_button->Location = System::Drawing::Point(8, 76);
    this->open_register_button->Margin = System::Windows::Forms::Padding(8);
    this->open_register_button->Name = L"open_register_button";
    this->open_register_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
    this->open_register_button->Size = System::Drawing::Size(181, 52);
    this->open_register_button->TabIndex = 1;
    this->open_register_button->Text = L"Register";
    this->open_register_button->UseVisualStyleBackColor = true;
    this->open_register_button->Click += gcnew System::EventHandler(this, &Main::open_register_button_Click);
    // 
    // open_history_button
    // 
    this->open_history_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
    this->open_history_button->AutoSize = true;
    this->open_history_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->open_history_button->Location = System::Drawing::Point(8, 144);
    this->open_history_button->Margin = System::Windows::Forms::Padding(8);
    this->open_history_button->Name = L"open_history_button";
    this->open_history_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
    this->open_history_button->Size = System::Drawing::Size(181, 52);
    this->open_history_button->TabIndex = 3;
    this->open_history_button->Text = L"History";
    this->open_history_button->UseVisualStyleBackColor = true;
    // 
    // open_settings_button
    // 
    this->open_settings_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
    this->open_settings_button->AutoSize = true;
    this->open_settings_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->open_settings_button->Location = System::Drawing::Point(8, 212);
    this->open_settings_button->Margin = System::Windows::Forms::Padding(8);
    this->open_settings_button->Name = L"open_settings_button";
    this->open_settings_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
    this->open_settings_button->Size = System::Drawing::Size(181, 52);
    this->open_settings_button->TabIndex = 4;
    this->open_settings_button->Text = L"Settings";
    this->open_settings_button->UseVisualStyleBackColor = true;
    // 
    // quit_button
    // 
    this->quit_button->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
    this->quit_button->AutoSize = true;
    this->quit_button->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->quit_button->Location = System::Drawing::Point(8, 280);
    this->quit_button->Margin = System::Windows::Forms::Padding(8);
    this->quit_button->Name = L"quit_button";
    this->quit_button->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
    this->quit_button->Size = System::Drawing::Size(181, 52);
    this->quit_button->TabIndex = 2;
    this->quit_button->Text = L"Quit to desktop";
    this->quit_button->UseVisualStyleBackColor = true;
    this->quit_button->Click += gcnew System::EventHandler(this, &Main::quit_button_Click);
    // 
    // main_menu_buttons
    // 
    this->main_menu_buttons->Anchor = System::Windows::Forms::AnchorStyles::None;
    this->main_menu_buttons->AutoSize = true;
    this->main_menu_buttons->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
    this->main_menu_buttons->ColumnCount = 1;
    this->main_menu_buttons->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
    this->main_menu_buttons->Controls->Add(this->quit_button, 0, 4);
    this->main_menu_buttons->Controls->Add(this->open_register_button, 0, 1);
    this->main_menu_buttons->Controls->Add(this->open_settings_button, 0, 3);
    this->main_menu_buttons->Controls->Add(this->open_history_button, 0, 2);
    this->main_menu_buttons->Controls->Add(this->open_login_button, 0, 0);
    this->main_menu_buttons->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel,
        static_cast<System::Byte>(238)));
    this->main_menu_buttons->Location = System::Drawing::Point(301, 130);
    this->main_menu_buttons->Margin = System::Windows::Forms::Padding(0);
    this->main_menu_buttons->Name = L"main_menu_buttons";
    this->main_menu_buttons->RowCount = 5;
    this->main_menu_buttons->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
    this->main_menu_buttons->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
    this->main_menu_buttons->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
    this->main_menu_buttons->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
    this->main_menu_buttons->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
    this->main_menu_buttons->Size = System::Drawing::Size(197, 340);
    this->main_menu_buttons->TabIndex = 5;
    // 
    // tableLayoutPanel2
    // 
    this->tableLayoutPanel2->ColumnCount = 1;
    this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        50)));
    this->tableLayoutPanel2->Controls->Add(this->main_menu_buttons, 0, 0);
    this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
    this->tableLayoutPanel2->Location = System::Drawing::Point(0, 0);
    this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
    this->tableLayoutPanel2->RowCount = 1;
    this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
    this->tableLayoutPanel2->Size = System::Drawing::Size(800, 600);
    this->tableLayoutPanel2->TabIndex = 6;
    // 
    // Main
    // 
    this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
    this->ClientSize = System::Drawing::Size(784, 561);
    this->Controls->Add(this->tableLayoutPanel2);
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
    this->MinimumSize = System::Drawing::Size(800, 600);
    this->Name = L"Main";
    this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
    this->Text = L"Mastermind";
    this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
    this->main_menu_buttons->ResumeLayout(false);
    this->main_menu_buttons->PerformLayout();
    this->tableLayoutPanel2->ResumeLayout(false);
    this->tableLayoutPanel2->PerformLayout();
    this->ResumeLayout(false);

}

System::Void Mastermind::Main::quit_button_Click(System::Object^ sender, System::EventArgs^ e)
{
  this->Close();
}

[System::STAThread]

int Main(array<System::String^>^ args) {
  System::Windows::Forms::Application::EnableVisualStyles();
  System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
  Mastermind::Main form;
  System::Windows::Forms::Application::Run(% form);
  return 0;
}
#include "Game.h"

Mastermind::Game::Game(void) {
  InitializeComponent();
}

Mastermind::Game::~Game() {
  if (components) {
    delete components;
  }
}

System::Void Mastermind::Game::timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
  this->label1->Text = TimeSpan::FromSeconds(++time).ToString("mm\\:ss");
}

System::Void Mastermind::Game::Game_Load(System::Object^ sender, System::EventArgs^ e) {
  this->time = 0;
  this->timer1->Start();
  row = column = 0;
  info_row = info_column = 4;
  pegs = gcnew cli::array<Peg^, 2>{
    { button_1_1, button_1_2, button_1_3, button_1_4, button_1_5, button_1_6, button_1_7, button_1_8 },
    { button_2_1, button_2_2, button_2_3, button_2_4, button_2_5, button_2_6, button_2_7, button_2_8 },
    { button_3_1, button_3_2, button_3_3, button_3_4, button_3_5, button_3_6, button_3_7, button_3_8 },
    { button_4_1, button_4_2, button_4_3, button_4_4, button_4_5, button_4_6, button_4_7, button_4_8 },
    { button_5_1, button_5_2, button_5_3, button_5_4, button_5_5, button_5_6, button_5_7, button_5_8 },
    { button_6_1, button_6_2, button_6_3, button_6_4, button_6_5, button_6_6, button_6_7, button_6_8 },
    { button_7_1, button_7_2, button_7_3, button_7_4, button_7_5, button_7_6, button_7_7, button_7_8 },
    { button_8_1, button_8_2, button_8_3, button_8_4, button_8_5, button_8_6, button_8_7, button_8_8 },
    { button_9_1, button_9_2, button_9_3, button_9_4, button_9_5, button_9_6, button_9_7, button_9_8 },
    { button_10_1, button_10_2, button_10_3, button_10_4, button_10_5, button_10_6, button_10_7, button_10_8 },
    { button_11_1, button_11_2, button_11_3, button_11_4, button_11_5, button_11_6, button_11_7, button_11_8 },
    { button_12_1, button_12_2, button_12_3, button_12_4, button_12_5, button_12_6, button_12_7, button_12_8 }
  };

  input_pegs = gcnew cli::array<Peg^, 1>{
    button_red, button_green, button_blue, button_yellow, button_purple, button_lime, button_cyan, button_orange
  };
  game = gcnew MastermindGame(input_pegs, pegs);
  for each (Peg ^ peg in game->pegs) {
    peg->setColor("DarkGray");
  }
}

System::Void Mastermind::Game::button_quit_Click(System::Object^ sender, System::EventArgs^ e)
{
  Close();
}

System::Void Mastermind::Game::Game_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
  timer1->Stop();
  time = 0;
  this->label1->Text = TimeSpan::FromSeconds(0).ToString("mm\\:ss");
}

System::Collections::Generic::List<System::String^>^ operator+(System::Collections::Generic::List<System::String^>^ list, System::String^ string) {
  list->Add(string);
  return list;
}

bool operator==(System::Collections::Generic::List<System::String^>^ list1, System::Collections::Generic::List<System::String^>^ list2) {
  for (int i = 0; i < list1->Count; i++) {
    if (list1[i] != list2[i])
      return false;
  }
  return true;
}

System::Void Mastermind::Game::ColorButton_Click(System::Object^ sender, System::EventArgs^ e)
{
  for each (Peg ^ input_peg in game->input_pegs)
  {
    if (input_peg != sender) continue;

    game->pegs[row, column++]->setColor(input_peg->getColor());
    game->attempt += input_peg->getColor();

    if (column != 4) break;

    if (row == 11) {
      timer1->Stop();
      MessageBox::Show("Failure", "Failure", MessageBoxButtons::OK, MessageBoxIcon::Warning);
      System::Data::SqlClient::SqlConnection^ conDatabase = gcnew System::Data::SqlClient::SqlConnection("Data Source=localhost\\SQLEXPRESS;Initial Catalog=mastermind;Integrated Security=SSPI");
      conDatabase->Open();
      String^ query = "UPDATE [stats] SET [failures] = [failures] + 1 FROM [stats] JOIN [users] ON [users].[id] = [stats].[user_id] WHERE [users].[username] = '" + username + "'";
      System::Data::SqlClient::SqlCommand^ cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
      cmd->ExecuteNonQuery();
      delete cmd;
      conDatabase->Close();
      delete conDatabase;
      Close();
      break;
    }

    column = 0;
    for (int i = 0; i < game->attempt->Count; i++) {
      if (game->attempt[i] == game->result[i]) {
        game->black_count++;
      }
    }

    System::Collections::Generic::SortedSet<String^>^ attempt_set;
    attempt_set = gcnew System::Collections::Generic::SortedSet<String^>;
    for (int i = 0; i < game->attempt->Count; i++) {
      attempt_set->Add(game->attempt[i]);
    }
    int result_element_count = 0;
    int attempt_element_count = 0;
    for each (String ^ element in attempt_set) {
      for (int j = 0; j < game->result->Count; j++) {
        if (element == game->result[j])
          result_element_count++;
      }
      for (int j = 0; j < game->attempt->Count; j++) {
        if (element == game->attempt[j])
          attempt_element_count++;
      }
      game->white_count +=
        (result_element_count > attempt_element_count) ?
        result_element_count - (result_element_count - attempt_element_count) :
        result_element_count;
      result_element_count = 0;
      attempt_element_count = 0;
    }
    delete attempt_set;
    game->white_count -= game->black_count;

    while (game->black_count > 0) {
      game->pegs[row, info_column++]->setColor("Black");
      game->black_count--;
    }
    while (game->white_count > 0) {
      game->pegs[row, info_column++]->setColor("White");
      game->white_count--;
    }

    if (game->attempt == game->result) {
      timer1->Stop();
      MessageBox::Show("You win " + this->username + "!\nAttempt number: " + (row + 1) + "\nYour time: " + label1->Text, "Win", MessageBoxButtons::OK, MessageBoxIcon::Information);
      System::Data::SqlClient::SqlConnection^ conDatabase = gcnew System::Data::SqlClient::SqlConnection("Data Source=localhost\\SQLEXPRESS;Initial Catalog=mastermind;Integrated Security=SSPI");
      conDatabase->Open();
      String^ query = "UPDATE [stats] SET [best time] = DATEADD(SECOND," + time + ", 0) FROM [stats] JOIN [users] ON [users].[id] = [stats].[user_id] WHERE ([best time] IS NULL OR [best time] > CONVERT(TIME(0), DATEADD(ss, " + time + ", 0))) AND [users].[username] = '" + username + "'";
      System::Data::SqlClient::SqlCommand^ cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
      cmd->ExecuteNonQuery();
      query = "UPDATE [stats] SET [wins] = [wins] + 1 FROM [stats] JOIN [users] ON [users].[id] = [stats].[user_id] WHERE [users].[username] = '" + username + "'";
      cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
      cmd->ExecuteNonQuery();
      delete cmd;
      conDatabase->Close();
      delete conDatabase;
      Close();
      break;
    }

    info_column = 4;
    row++;
    game->attempt->Clear();
    break;
  }
  return System::Void();
}


void Mastermind::Game::InitializeComponent(void) {
  this->components = (gcnew System::ComponentModel::Container());
  this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->tableLayoutPanel5 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->label1 = (gcnew System::Windows::Forms::Label());
  this->button_quit = (gcnew System::Windows::Forms::Button());
  this->tableLayoutPanel6 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->button_12_1 = (gcnew Peg);
  this->button_12_2 = (gcnew Peg);
  this->button_12_3 = (gcnew Peg);
  this->button_12_4 = (gcnew Peg);
  this->button_11_1 = (gcnew Peg);
  this->button_11_2 = (gcnew Peg);
  this->button_11_3 = (gcnew Peg);
  this->button_11_4 = (gcnew Peg);
  this->button_10_1 = (gcnew Peg);
  this->button_10_2 = (gcnew Peg);
  this->button_10_3 = (gcnew Peg);
  this->button_10_4 = (gcnew Peg);
  this->button_9_1 = (gcnew Peg);
  this->button_9_2 = (gcnew Peg);
  this->button_9_3 = (gcnew Peg);
  this->button_9_4 = (gcnew Peg);
  this->button_8_1 = (gcnew Peg);
  this->button_8_2 = (gcnew Peg);
  this->button_8_3 = (gcnew Peg);
  this->button_8_4 = (gcnew Peg);
  this->button_7_1 = (gcnew Peg);
  this->button_7_2 = (gcnew Peg);
  this->button_7_3 = (gcnew Peg);
  this->button_7_4 = (gcnew Peg);
  this->button_6_1 = (gcnew Peg);
  this->button_6_2 = (gcnew Peg);
  this->button_6_3 = (gcnew Peg);
  this->button_6_4 = (gcnew Peg);
  this->button_5_1 = (gcnew Peg);
  this->button_5_2 = (gcnew Peg);
  this->button_5_3 = (gcnew Peg);
  this->button_5_4 = (gcnew Peg);
  this->button_4_2 = (gcnew Peg);
  this->button_4_1 = (gcnew Peg);
  this->button_4_3 = (gcnew Peg);
  this->button_4_4 = (gcnew Peg);
  this->button_3_1 = (gcnew Peg);
  this->button_3_2 = (gcnew Peg);
  this->button_3_3 = (gcnew Peg);
  this->button_3_4 = (gcnew Peg);
  this->button_2_1 = (gcnew Peg);
  this->button_2_2 = (gcnew Peg);
  this->button_2_3 = (gcnew Peg);
  this->button_2_4 = (gcnew Peg);
  this->button_1_1 = (gcnew Peg);
  this->button_1_2 = (gcnew Peg);
  this->button_1_3 = (gcnew Peg);
  this->button_1_4 = (gcnew Peg);
  this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->button_12_5 = (gcnew Peg);
  this->button_12_6 = (gcnew Peg);
  this->button_12_7 = (gcnew Peg);
  this->button_12_8 = (gcnew Peg);
  this->button_11_5 = (gcnew Peg);
  this->button_11_6 = (gcnew Peg);
  this->button_11_7 = (gcnew Peg);
  this->button_11_8 = (gcnew Peg);
  this->button_10_5 = (gcnew Peg);
  this->button_10_6 = (gcnew Peg);
  this->button_10_7 = (gcnew Peg);
  this->button_10_8 = (gcnew Peg);
  this->button_9_5 = (gcnew Peg);
  this->button_9_6 = (gcnew Peg);
  this->button_9_7 = (gcnew Peg);
  this->button_9_8 = (gcnew Peg);
  this->button_8_5 = (gcnew Peg);
  this->button_8_6 = (gcnew Peg);
  this->button_8_7 = (gcnew Peg);
  this->button_8_8 = (gcnew Peg);
  this->button_7_5 = (gcnew Peg);
  this->button_7_6 = (gcnew Peg);
  this->button_7_7 = (gcnew Peg);
  this->button_7_8 = (gcnew Peg);
  this->button_6_5 = (gcnew Peg);
  this->button_6_6 = (gcnew Peg);
  this->button_6_7 = (gcnew Peg);
  this->button_6_8 = (gcnew Peg);
  this->button_5_5 = (gcnew Peg);
  this->button_5_6 = (gcnew Peg);
  this->button_5_7 = (gcnew Peg);
  this->button_5_8 = (gcnew Peg);
  this->button_4_6 = (gcnew Peg);
  this->button_4_5 = (gcnew Peg);
  this->button_4_7 = (gcnew Peg);
  this->button_4_8 = (gcnew Peg);
  this->button_3_5 = (gcnew Peg);
  this->button_3_6 = (gcnew Peg);
  this->button_3_7 = (gcnew Peg);
  this->button_3_8 = (gcnew Peg);
  this->button_2_5 = (gcnew Peg);
  this->button_2_6 = (gcnew Peg);
  this->button_2_7 = (gcnew Peg);
  this->button_2_8 = (gcnew Peg);
  this->button_1_5 = (gcnew Peg);
  this->button_1_6 = (gcnew Peg);
  this->button_1_7 = (gcnew Peg);
  this->button_1_8 = (gcnew Peg);
  this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->button_purple = (gcnew Peg);
  this->button_lime = (gcnew Peg);
  this->button_cyan = (gcnew Peg);
  this->button_orange = (gcnew Peg);
  this->button_red = (gcnew Peg);
  this->button_green = (gcnew Peg);
  this->button_blue = (gcnew Peg);
  this->button_yellow = (gcnew Peg);
  this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
  this->tableLayoutPanel1->SuspendLayout();
  this->tableLayoutPanel5->SuspendLayout();
  this->tableLayoutPanel6->SuspendLayout();
  this->tableLayoutPanel2->SuspendLayout();
  this->tableLayoutPanel3->SuspendLayout();
  this->tableLayoutPanel4->SuspendLayout();
  this->SuspendLayout();
  // 
  // tableLayoutPanel1
  // 
  this->tableLayoutPanel1->ColumnCount = 2;
  this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    33.33333F)));
  this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    33.33333F)));
  this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel5, 1, 1);
  this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel6, 0, 0);
  this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel4, 1, 0);
  this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
  this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
  this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
  this->tableLayoutPanel1->RowCount = 2;
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
  this->tableLayoutPanel1->Size = System::Drawing::Size(800, 600);
  this->tableLayoutPanel1->TabIndex = 0;
  // 
  // tableLayoutPanel5
  // 
  this->tableLayoutPanel5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->tableLayoutPanel5->AutoSize = true;
  this->tableLayoutPanel5->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->tableLayoutPanel5->ColumnCount = 2;
  this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel5->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel5->Controls->Add(this->label1, 0, 0);
  this->tableLayoutPanel5->Controls->Add(this->button_quit, 1, 0);
  this->tableLayoutPanel5->Location = System::Drawing::Point(520, 539);
  this->tableLayoutPanel5->Name = L"tableLayoutPanel5";
  this->tableLayoutPanel5->RowCount = 1;
  this->tableLayoutPanel5->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
  this->tableLayoutPanel5->Size = System::Drawing::Size(160, 58);
  this->tableLayoutPanel5->TabIndex = 4;
  // 
  // label1
  // 
  this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->label1->AutoSize = true;
  this->label1->Location = System::Drawing::Point(3, 18);
  this->label1->Name = L"label1";
  this->label1->Size = System::Drawing::Size(55, 22);
  this->label1->TabIndex = 0;
  this->label1->Text = L"00:00";
  // 
  // button_quit
  // 
  this->button_quit->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_quit->AutoSize = true;
  this->button_quit->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->button_quit->Location = System::Drawing::Point(64, 3);
  this->button_quit->Name = L"button_quit";
  this->button_quit->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->button_quit->Size = System::Drawing::Size(93, 52);
  this->button_quit->TabIndex = 8;
  this->button_quit->Text = L"Quit";
  this->button_quit->UseVisualStyleBackColor = true;
  this->button_quit->Click += gcnew System::EventHandler(this, &Game::button_quit_Click);
  // 
  // tableLayoutPanel6
  // 
  this->tableLayoutPanel6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->tableLayoutPanel6->AutoSize = true;
  this->tableLayoutPanel6->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->tableLayoutPanel6->ColumnCount = 2;
  this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    50)));
  this->tableLayoutPanel6->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    50)));
  this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel2, 0, 0);
  this->tableLayoutPanel6->Controls->Add(this->tableLayoutPanel3, 1, 0);
  this->tableLayoutPanel6->Location = System::Drawing::Point(50, 81);
  this->tableLayoutPanel6->Name = L"tableLayoutPanel6";
  this->tableLayoutPanel6->RowCount = 1;
  this->tableLayoutPanel1->SetRowSpan(this->tableLayoutPanel6, 2);
  this->tableLayoutPanel6->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
  this->tableLayoutPanel6->Size = System::Drawing::Size(300, 438);
  this->tableLayoutPanel6->TabIndex = 5;
  // 
  // tableLayoutPanel2
  // 
  this->tableLayoutPanel2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->tableLayoutPanel2->AutoSize = true;
  this->tableLayoutPanel2->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->tableLayoutPanel2->ColumnCount = 4;
  this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel2->Controls->Add(this->button_12_1, 0, 0);
  this->tableLayoutPanel2->Controls->Add(this->button_12_2, 1, 0);
  this->tableLayoutPanel2->Controls->Add(this->button_12_3, 2, 0);
  this->tableLayoutPanel2->Controls->Add(this->button_12_4, 3, 0);
  this->tableLayoutPanel2->Controls->Add(this->button_11_1, 0, 1);
  this->tableLayoutPanel2->Controls->Add(this->button_11_2, 1, 1);
  this->tableLayoutPanel2->Controls->Add(this->button_11_3, 2, 1);
  this->tableLayoutPanel2->Controls->Add(this->button_11_4, 3, 1);
  this->tableLayoutPanel2->Controls->Add(this->button_10_1, 0, 2);
  this->tableLayoutPanel2->Controls->Add(this->button_10_2, 1, 2);
  this->tableLayoutPanel2->Controls->Add(this->button_10_3, 2, 2);
  this->tableLayoutPanel2->Controls->Add(this->button_10_4, 3, 2);
  this->tableLayoutPanel2->Controls->Add(this->button_9_1, 0, 3);
  this->tableLayoutPanel2->Controls->Add(this->button_9_2, 1, 3);
  this->tableLayoutPanel2->Controls->Add(this->button_9_3, 2, 3);
  this->tableLayoutPanel2->Controls->Add(this->button_9_4, 3, 3);
  this->tableLayoutPanel2->Controls->Add(this->button_8_1, 0, 4);
  this->tableLayoutPanel2->Controls->Add(this->button_8_2, 1, 4);
  this->tableLayoutPanel2->Controls->Add(this->button_8_3, 2, 4);
  this->tableLayoutPanel2->Controls->Add(this->button_8_4, 3, 4);
  this->tableLayoutPanel2->Controls->Add(this->button_7_1, 0, 5);
  this->tableLayoutPanel2->Controls->Add(this->button_7_2, 1, 5);
  this->tableLayoutPanel2->Controls->Add(this->button_7_3, 2, 5);
  this->tableLayoutPanel2->Controls->Add(this->button_7_4, 3, 5);
  this->tableLayoutPanel2->Controls->Add(this->button_6_1, 0, 6);
  this->tableLayoutPanel2->Controls->Add(this->button_6_2, 1, 6);
  this->tableLayoutPanel2->Controls->Add(this->button_6_3, 2, 6);
  this->tableLayoutPanel2->Controls->Add(this->button_6_4, 3, 6);
  this->tableLayoutPanel2->Controls->Add(this->button_5_1, 0, 7);
  this->tableLayoutPanel2->Controls->Add(this->button_5_2, 1, 7);
  this->tableLayoutPanel2->Controls->Add(this->button_5_3, 2, 7);
  this->tableLayoutPanel2->Controls->Add(this->button_5_4, 3, 7);
  this->tableLayoutPanel2->Controls->Add(this->button_4_2, 1, 8);
  this->tableLayoutPanel2->Controls->Add(this->button_4_1, 0, 8);
  this->tableLayoutPanel2->Controls->Add(this->button_4_3, 2, 8);
  this->tableLayoutPanel2->Controls->Add(this->button_4_4, 3, 8);
  this->tableLayoutPanel2->Controls->Add(this->button_3_1, 0, 9);
  this->tableLayoutPanel2->Controls->Add(this->button_3_2, 1, 9);
  this->tableLayoutPanel2->Controls->Add(this->button_3_3, 2, 9);
  this->tableLayoutPanel2->Controls->Add(this->button_3_4, 3, 9);
  this->tableLayoutPanel2->Controls->Add(this->button_2_1, 0, 10);
  this->tableLayoutPanel2->Controls->Add(this->button_2_2, 1, 10);
  this->tableLayoutPanel2->Controls->Add(this->button_2_3, 2, 10);
  this->tableLayoutPanel2->Controls->Add(this->button_2_4, 3, 10);
  this->tableLayoutPanel2->Controls->Add(this->button_1_1, 0, 11);
  this->tableLayoutPanel2->Controls->Add(this->button_1_2, 1, 11);
  this->tableLayoutPanel2->Controls->Add(this->button_1_3, 2, 11);
  this->tableLayoutPanel2->Controls->Add(this->button_1_4, 3, 11);
  this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
  this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
  this->tableLayoutPanel2->RowCount = 12;
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel2->Size = System::Drawing::Size(144, 432);
  this->tableLayoutPanel2->TabIndex = 0;
  // 
  // button_12_1
  // 
  this->button_12_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_1->Enabled = false;
  this->button_12_1->Location = System::Drawing::Point(3, 3);
  this->button_12_1->Name = L"button_12_1";
  this->button_12_1->Size = System::Drawing::Size(30, 30);
  this->button_12_1->TabIndex = 0;
  this->button_12_1->UseVisualStyleBackColor = true;
  // 
  // button_12_2
  // 
  this->button_12_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_2->Enabled = false;
  this->button_12_2->Location = System::Drawing::Point(39, 3);
  this->button_12_2->Name = L"button_12_2";
  this->button_12_2->Size = System::Drawing::Size(30, 30);
  this->button_12_2->TabIndex = 1;
  this->button_12_2->UseVisualStyleBackColor = true;
  // 
  // button_12_3
  // 
  this->button_12_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_3->Enabled = false;
  this->button_12_3->Location = System::Drawing::Point(75, 3);
  this->button_12_3->Name = L"button_12_3";
  this->button_12_3->Size = System::Drawing::Size(30, 30);
  this->button_12_3->TabIndex = 2;
  this->button_12_3->UseVisualStyleBackColor = true;
  // 
  // button_12_4
  // 
  this->button_12_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_4->Enabled = false;
  this->button_12_4->Location = System::Drawing::Point(111, 3);
  this->button_12_4->Name = L"button_12_4";
  this->button_12_4->Size = System::Drawing::Size(30, 30);
  this->button_12_4->TabIndex = 3;
  this->button_12_4->UseVisualStyleBackColor = true;
  // 
  // button_11_1
  // 
  this->button_11_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_1->Enabled = false;
  this->button_11_1->Location = System::Drawing::Point(3, 39);
  this->button_11_1->Name = L"button_11_1";
  this->button_11_1->Size = System::Drawing::Size(30, 30);
  this->button_11_1->TabIndex = 4;
  this->button_11_1->UseVisualStyleBackColor = true;
  // 
  // button_11_2
  // 
  this->button_11_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_2->Enabled = false;
  this->button_11_2->Location = System::Drawing::Point(39, 39);
  this->button_11_2->Name = L"button_11_2";
  this->button_11_2->Size = System::Drawing::Size(30, 30);
  this->button_11_2->TabIndex = 5;
  this->button_11_2->UseVisualStyleBackColor = true;
  // 
  // button_11_3
  // 
  this->button_11_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_3->Enabled = false;
  this->button_11_3->Location = System::Drawing::Point(75, 39);
  this->button_11_3->Name = L"button_11_3";
  this->button_11_3->Size = System::Drawing::Size(30, 30);
  this->button_11_3->TabIndex = 6;
  this->button_11_3->UseVisualStyleBackColor = true;
  // 
  // button_11_4
  // 
  this->button_11_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_4->Enabled = false;
  this->button_11_4->Location = System::Drawing::Point(111, 39);
  this->button_11_4->Name = L"button_11_4";
  this->button_11_4->Size = System::Drawing::Size(30, 30);
  this->button_11_4->TabIndex = 7;
  this->button_11_4->UseVisualStyleBackColor = true;
  // 
  // button_10_1
  // 
  this->button_10_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_1->Enabled = false;
  this->button_10_1->Location = System::Drawing::Point(3, 75);
  this->button_10_1->Name = L"button_10_1";
  this->button_10_1->Size = System::Drawing::Size(30, 30);
  this->button_10_1->TabIndex = 8;
  this->button_10_1->UseVisualStyleBackColor = true;
  // 
  // button_10_2
  // 
  this->button_10_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_2->Enabled = false;
  this->button_10_2->Location = System::Drawing::Point(39, 75);
  this->button_10_2->Name = L"button_10_2";
  this->button_10_2->Size = System::Drawing::Size(30, 30);
  this->button_10_2->TabIndex = 9;
  this->button_10_2->UseVisualStyleBackColor = true;
  // 
  // button_10_3
  // 
  this->button_10_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_3->Enabled = false;
  this->button_10_3->Location = System::Drawing::Point(75, 75);
  this->button_10_3->Name = L"button_10_3";
  this->button_10_3->Size = System::Drawing::Size(30, 30);
  this->button_10_3->TabIndex = 10;
  this->button_10_3->UseVisualStyleBackColor = true;
  // 
  // button_10_4
  // 
  this->button_10_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_4->Enabled = false;
  this->button_10_4->Location = System::Drawing::Point(111, 75);
  this->button_10_4->Name = L"button_10_4";
  this->button_10_4->Size = System::Drawing::Size(30, 30);
  this->button_10_4->TabIndex = 11;
  this->button_10_4->UseVisualStyleBackColor = true;
  // 
  // button_9_1
  // 
  this->button_9_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_1->Enabled = false;
  this->button_9_1->Location = System::Drawing::Point(3, 111);
  this->button_9_1->Name = L"button_9_1";
  this->button_9_1->Size = System::Drawing::Size(30, 30);
  this->button_9_1->TabIndex = 12;
  this->button_9_1->UseVisualStyleBackColor = true;
  // 
  // button_9_2
  // 
  this->button_9_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_2->Enabled = false;
  this->button_9_2->Location = System::Drawing::Point(39, 111);
  this->button_9_2->Name = L"button_9_2";
  this->button_9_2->Size = System::Drawing::Size(30, 30);
  this->button_9_2->TabIndex = 13;
  this->button_9_2->UseVisualStyleBackColor = true;
  // 
  // button_9_3
  // 
  this->button_9_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_3->Enabled = false;
  this->button_9_3->Location = System::Drawing::Point(75, 111);
  this->button_9_3->Name = L"button_9_3";
  this->button_9_3->Size = System::Drawing::Size(30, 30);
  this->button_9_3->TabIndex = 14;
  this->button_9_3->UseVisualStyleBackColor = true;
  // 
  // button_9_4
  // 
  this->button_9_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_4->Enabled = false;
  this->button_9_4->Location = System::Drawing::Point(111, 111);
  this->button_9_4->Name = L"button_9_4";
  this->button_9_4->Size = System::Drawing::Size(30, 30);
  this->button_9_4->TabIndex = 15;
  this->button_9_4->UseVisualStyleBackColor = true;
  // 
  // button_8_1
  // 
  this->button_8_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_1->Enabled = false;
  this->button_8_1->Location = System::Drawing::Point(3, 147);
  this->button_8_1->Name = L"button_8_1";
  this->button_8_1->Size = System::Drawing::Size(30, 30);
  this->button_8_1->TabIndex = 16;
  this->button_8_1->UseVisualStyleBackColor = true;
  // 
  // button_8_2
  // 
  this->button_8_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_2->Enabled = false;
  this->button_8_2->Location = System::Drawing::Point(39, 147);
  this->button_8_2->Name = L"button_8_2";
  this->button_8_2->Size = System::Drawing::Size(30, 30);
  this->button_8_2->TabIndex = 17;
  this->button_8_2->UseVisualStyleBackColor = true;
  // 
  // button_8_3
  // 
  this->button_8_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_3->Enabled = false;
  this->button_8_3->Location = System::Drawing::Point(75, 147);
  this->button_8_3->Name = L"button_8_3";
  this->button_8_3->Size = System::Drawing::Size(30, 30);
  this->button_8_3->TabIndex = 18;
  this->button_8_3->UseVisualStyleBackColor = true;
  // 
  // button_8_4
  // 
  this->button_8_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_4->Enabled = false;
  this->button_8_4->Location = System::Drawing::Point(111, 147);
  this->button_8_4->Name = L"button_8_4";
  this->button_8_4->Size = System::Drawing::Size(30, 30);
  this->button_8_4->TabIndex = 19;
  this->button_8_4->UseVisualStyleBackColor = true;
  // 
  // button_7_1
  // 
  this->button_7_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_1->Enabled = false;
  this->button_7_1->Location = System::Drawing::Point(3, 183);
  this->button_7_1->Name = L"button_7_1";
  this->button_7_1->Size = System::Drawing::Size(30, 30);
  this->button_7_1->TabIndex = 20;
  this->button_7_1->UseVisualStyleBackColor = true;
  // 
  // button_7_2
  // 
  this->button_7_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_2->Enabled = false;
  this->button_7_2->Location = System::Drawing::Point(39, 183);
  this->button_7_2->Name = L"button_7_2";
  this->button_7_2->Size = System::Drawing::Size(30, 30);
  this->button_7_2->TabIndex = 21;
  this->button_7_2->UseVisualStyleBackColor = true;
  // 
  // button_7_3
  // 
  this->button_7_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_3->Enabled = false;
  this->button_7_3->Location = System::Drawing::Point(75, 183);
  this->button_7_3->Name = L"button_7_3";
  this->button_7_3->Size = System::Drawing::Size(30, 30);
  this->button_7_3->TabIndex = 22;
  this->button_7_3->UseVisualStyleBackColor = true;
  // 
  // button_7_4
  // 
  this->button_7_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_4->Enabled = false;
  this->button_7_4->Location = System::Drawing::Point(111, 183);
  this->button_7_4->Name = L"button_7_4";
  this->button_7_4->Size = System::Drawing::Size(30, 30);
  this->button_7_4->TabIndex = 23;
  this->button_7_4->UseVisualStyleBackColor = true;
  // 
  // button_6_1
  // 
  this->button_6_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_1->Enabled = false;
  this->button_6_1->Location = System::Drawing::Point(3, 219);
  this->button_6_1->Name = L"button_6_1";
  this->button_6_1->Size = System::Drawing::Size(30, 30);
  this->button_6_1->TabIndex = 24;
  this->button_6_1->UseVisualStyleBackColor = true;
  // 
  // button_6_2
  // 
  this->button_6_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_2->Enabled = false;
  this->button_6_2->Location = System::Drawing::Point(39, 219);
  this->button_6_2->Name = L"button_6_2";
  this->button_6_2->Size = System::Drawing::Size(30, 30);
  this->button_6_2->TabIndex = 25;
  this->button_6_2->UseVisualStyleBackColor = true;
  // 
  // button_6_3
  // 
  this->button_6_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_3->Enabled = false;
  this->button_6_3->Location = System::Drawing::Point(75, 219);
  this->button_6_3->Name = L"button_6_3";
  this->button_6_3->Size = System::Drawing::Size(30, 30);
  this->button_6_3->TabIndex = 26;
  this->button_6_3->UseVisualStyleBackColor = true;
  // 
  // button_6_4
  // 
  this->button_6_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_4->Enabled = false;
  this->button_6_4->Location = System::Drawing::Point(111, 219);
  this->button_6_4->Name = L"button_6_4";
  this->button_6_4->Size = System::Drawing::Size(30, 30);
  this->button_6_4->TabIndex = 27;
  this->button_6_4->UseVisualStyleBackColor = true;
  // 
  // button_5_1
  // 
  this->button_5_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_1->Enabled = false;
  this->button_5_1->Location = System::Drawing::Point(3, 255);
  this->button_5_1->Name = L"button_5_1";
  this->button_5_1->Size = System::Drawing::Size(30, 30);
  this->button_5_1->TabIndex = 28;
  this->button_5_1->UseVisualStyleBackColor = true;
  // 
  // button_5_2
  // 
  this->button_5_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_2->Enabled = false;
  this->button_5_2->Location = System::Drawing::Point(39, 255);
  this->button_5_2->Name = L"button_5_2";
  this->button_5_2->Size = System::Drawing::Size(30, 30);
  this->button_5_2->TabIndex = 29;
  this->button_5_2->UseVisualStyleBackColor = true;
  // 
  // button_5_3
  // 
  this->button_5_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_3->Enabled = false;
  this->button_5_3->Location = System::Drawing::Point(75, 255);
  this->button_5_3->Name = L"button_5_3";
  this->button_5_3->Size = System::Drawing::Size(30, 30);
  this->button_5_3->TabIndex = 30;
  this->button_5_3->UseVisualStyleBackColor = true;
  // 
  // button_5_4
  // 
  this->button_5_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_4->Enabled = false;
  this->button_5_4->Location = System::Drawing::Point(111, 255);
  this->button_5_4->Name = L"button_5_4";
  this->button_5_4->Size = System::Drawing::Size(30, 30);
  this->button_5_4->TabIndex = 31;
  this->button_5_4->UseVisualStyleBackColor = true;
  // 
  // button_4_2
  // 
  this->button_4_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_2->Enabled = false;
  this->button_4_2->Location = System::Drawing::Point(39, 291);
  this->button_4_2->Name = L"button_4_2";
  this->button_4_2->Size = System::Drawing::Size(30, 30);
  this->button_4_2->TabIndex = 32;
  this->button_4_2->UseVisualStyleBackColor = true;
  // 
  // button_4_1
  // 
  this->button_4_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_1->Enabled = false;
  this->button_4_1->Location = System::Drawing::Point(3, 291);
  this->button_4_1->Name = L"button_4_1";
  this->button_4_1->Size = System::Drawing::Size(30, 30);
  this->button_4_1->TabIndex = 33;
  this->button_4_1->UseVisualStyleBackColor = true;
  // 
  // button_4_3
  // 
  this->button_4_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_3->Enabled = false;
  this->button_4_3->Location = System::Drawing::Point(75, 291);
  this->button_4_3->Name = L"button_4_3";
  this->button_4_3->Size = System::Drawing::Size(30, 30);
  this->button_4_3->TabIndex = 34;
  this->button_4_3->UseVisualStyleBackColor = true;
  // 
  // button_4_4
  // 
  this->button_4_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_4->Enabled = false;
  this->button_4_4->Location = System::Drawing::Point(111, 291);
  this->button_4_4->Name = L"button_4_4";
  this->button_4_4->Size = System::Drawing::Size(30, 30);
  this->button_4_4->TabIndex = 35;
  this->button_4_4->UseVisualStyleBackColor = true;
  // 
  // button_3_1
  // 
  this->button_3_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_1->Enabled = false;
  this->button_3_1->Location = System::Drawing::Point(3, 327);
  this->button_3_1->Name = L"button_3_1";
  this->button_3_1->Size = System::Drawing::Size(30, 30);
  this->button_3_1->TabIndex = 36;
  this->button_3_1->UseVisualStyleBackColor = true;
  // 
  // button_3_2
  // 
  this->button_3_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_2->Enabled = false;
  this->button_3_2->Location = System::Drawing::Point(39, 327);
  this->button_3_2->Name = L"button_3_2";
  this->button_3_2->Size = System::Drawing::Size(30, 30);
  this->button_3_2->TabIndex = 37;
  this->button_3_2->UseVisualStyleBackColor = true;
  // 
  // button_3_3
  // 
  this->button_3_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_3->Enabled = false;
  this->button_3_3->Location = System::Drawing::Point(75, 327);
  this->button_3_3->Name = L"button_3_3";
  this->button_3_3->Size = System::Drawing::Size(30, 30);
  this->button_3_3->TabIndex = 38;
  this->button_3_3->UseVisualStyleBackColor = true;
  // 
  // button_3_4
  // 
  this->button_3_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_4->Enabled = false;
  this->button_3_4->Location = System::Drawing::Point(111, 327);
  this->button_3_4->Name = L"button_3_4";
  this->button_3_4->Size = System::Drawing::Size(30, 30);
  this->button_3_4->TabIndex = 39;
  this->button_3_4->UseVisualStyleBackColor = true;
  // 
  // button_2_1
  // 
  this->button_2_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_1->Enabled = false;
  this->button_2_1->Location = System::Drawing::Point(3, 363);
  this->button_2_1->Name = L"button_2_1";
  this->button_2_1->Size = System::Drawing::Size(30, 30);
  this->button_2_1->TabIndex = 40;
  this->button_2_1->UseVisualStyleBackColor = true;
  // 
  // button_2_2
  // 
  this->button_2_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_2->Enabled = false;
  this->button_2_2->Location = System::Drawing::Point(39, 363);
  this->button_2_2->Name = L"button_2_2";
  this->button_2_2->Size = System::Drawing::Size(30, 30);
  this->button_2_2->TabIndex = 41;
  this->button_2_2->UseVisualStyleBackColor = true;
  // 
  // button_2_3
  // 
  this->button_2_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_3->Enabled = false;
  this->button_2_3->Location = System::Drawing::Point(75, 363);
  this->button_2_3->Name = L"button_2_3";
  this->button_2_3->Size = System::Drawing::Size(30, 30);
  this->button_2_3->TabIndex = 42;
  this->button_2_3->UseVisualStyleBackColor = true;
  // 
  // button_2_4
  // 
  this->button_2_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_4->Enabled = false;
  this->button_2_4->Location = System::Drawing::Point(111, 363);
  this->button_2_4->Name = L"button_2_4";
  this->button_2_4->Size = System::Drawing::Size(30, 30);
  this->button_2_4->TabIndex = 43;
  this->button_2_4->UseVisualStyleBackColor = true;
  // 
  // button_1_1
  // 
  this->button_1_1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_1->Enabled = false;
  this->button_1_1->Location = System::Drawing::Point(3, 399);
  this->button_1_1->Name = L"button_1_1";
  this->button_1_1->Size = System::Drawing::Size(30, 30);
  this->button_1_1->TabIndex = 44;
  this->button_1_1->UseVisualStyleBackColor = true;
  // 
  // button_1_2
  // 
  this->button_1_2->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_2->Enabled = false;
  this->button_1_2->Location = System::Drawing::Point(39, 399);
  this->button_1_2->Name = L"button_1_2";
  this->button_1_2->Size = System::Drawing::Size(30, 30);
  this->button_1_2->TabIndex = 45;
  this->button_1_2->UseVisualStyleBackColor = true;
  // 
  // button_1_3
  // 
  this->button_1_3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_3->Enabled = false;
  this->button_1_3->Location = System::Drawing::Point(75, 399);
  this->button_1_3->Name = L"button_1_3";
  this->button_1_3->Size = System::Drawing::Size(30, 30);
  this->button_1_3->TabIndex = 46;
  this->button_1_3->UseVisualStyleBackColor = true;
  // 
  // button_1_4
  // 
  this->button_1_4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_4->Enabled = false;
  this->button_1_4->Location = System::Drawing::Point(111, 399);
  this->button_1_4->Name = L"button_1_4";
  this->button_1_4->Size = System::Drawing::Size(30, 30);
  this->button_1_4->TabIndex = 47;
  this->button_1_4->UseVisualStyleBackColor = true;
  // 
  // tableLayoutPanel3
  // 
  this->tableLayoutPanel3->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->tableLayoutPanel3->AutoSize = true;
  this->tableLayoutPanel3->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->tableLayoutPanel3->ColumnCount = 4;
  this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel3->Controls->Add(this->button_12_5, 0, 0);
  this->tableLayoutPanel3->Controls->Add(this->button_12_6, 1, 0);
  this->tableLayoutPanel3->Controls->Add(this->button_12_7, 2, 0);
  this->tableLayoutPanel3->Controls->Add(this->button_12_8, 3, 0);
  this->tableLayoutPanel3->Controls->Add(this->button_11_5, 0, 1);
  this->tableLayoutPanel3->Controls->Add(this->button_11_6, 1, 1);
  this->tableLayoutPanel3->Controls->Add(this->button_11_7, 2, 1);
  this->tableLayoutPanel3->Controls->Add(this->button_11_8, 3, 1);
  this->tableLayoutPanel3->Controls->Add(this->button_10_5, 0, 2);
  this->tableLayoutPanel3->Controls->Add(this->button_10_6, 1, 2);
  this->tableLayoutPanel3->Controls->Add(this->button_10_7, 2, 2);
  this->tableLayoutPanel3->Controls->Add(this->button_10_8, 3, 2);
  this->tableLayoutPanel3->Controls->Add(this->button_9_5, 0, 3);
  this->tableLayoutPanel3->Controls->Add(this->button_9_6, 1, 3);
  this->tableLayoutPanel3->Controls->Add(this->button_9_7, 2, 3);
  this->tableLayoutPanel3->Controls->Add(this->button_9_8, 3, 3);
  this->tableLayoutPanel3->Controls->Add(this->button_8_5, 0, 4);
  this->tableLayoutPanel3->Controls->Add(this->button_8_6, 1, 4);
  this->tableLayoutPanel3->Controls->Add(this->button_8_7, 2, 4);
  this->tableLayoutPanel3->Controls->Add(this->button_8_8, 3, 4);
  this->tableLayoutPanel3->Controls->Add(this->button_7_5, 0, 5);
  this->tableLayoutPanel3->Controls->Add(this->button_7_6, 1, 5);
  this->tableLayoutPanel3->Controls->Add(this->button_7_7, 2, 5);
  this->tableLayoutPanel3->Controls->Add(this->button_7_8, 3, 5);
  this->tableLayoutPanel3->Controls->Add(this->button_6_5, 0, 6);
  this->tableLayoutPanel3->Controls->Add(this->button_6_6, 1, 6);
  this->tableLayoutPanel3->Controls->Add(this->button_6_7, 2, 6);
  this->tableLayoutPanel3->Controls->Add(this->button_6_8, 3, 6);
  this->tableLayoutPanel3->Controls->Add(this->button_5_5, 0, 7);
  this->tableLayoutPanel3->Controls->Add(this->button_5_6, 1, 7);
  this->tableLayoutPanel3->Controls->Add(this->button_5_7, 2, 7);
  this->tableLayoutPanel3->Controls->Add(this->button_5_8, 3, 7);
  this->tableLayoutPanel3->Controls->Add(this->button_4_6, 1, 8);
  this->tableLayoutPanel3->Controls->Add(this->button_4_5, 0, 8);
  this->tableLayoutPanel3->Controls->Add(this->button_4_7, 2, 8);
  this->tableLayoutPanel3->Controls->Add(this->button_4_8, 3, 8);
  this->tableLayoutPanel3->Controls->Add(this->button_3_5, 0, 9);
  this->tableLayoutPanel3->Controls->Add(this->button_3_6, 1, 9);
  this->tableLayoutPanel3->Controls->Add(this->button_3_7, 2, 9);
  this->tableLayoutPanel3->Controls->Add(this->button_3_8, 3, 9);
  this->tableLayoutPanel3->Controls->Add(this->button_2_5, 0, 10);
  this->tableLayoutPanel3->Controls->Add(this->button_2_6, 1, 10);
  this->tableLayoutPanel3->Controls->Add(this->button_2_7, 2, 10);
  this->tableLayoutPanel3->Controls->Add(this->button_2_8, 3, 10);
  this->tableLayoutPanel3->Controls->Add(this->button_1_5, 0, 11);
  this->tableLayoutPanel3->Controls->Add(this->button_1_6, 1, 11);
  this->tableLayoutPanel3->Controls->Add(this->button_1_7, 2, 11);
  this->tableLayoutPanel3->Controls->Add(this->button_1_8, 3, 11);
  this->tableLayoutPanel3->Enabled = false;
  this->tableLayoutPanel3->Location = System::Drawing::Point(153, 3);
  this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
  this->tableLayoutPanel3->RowCount = 12;
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel3->Size = System::Drawing::Size(144, 432);
  this->tableLayoutPanel3->TabIndex = 3;
  // 
  // button_12_5
  // 
  this->button_12_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_5->Location = System::Drawing::Point(3, 3);
  this->button_12_5->Name = L"button_12_5";
  this->button_12_5->Size = System::Drawing::Size(30, 30);
  this->button_12_5->TabIndex = 0;
  this->button_12_5->UseVisualStyleBackColor = true;
  // 
  // button_12_6
  // 
  this->button_12_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_6->Location = System::Drawing::Point(39, 3);
  this->button_12_6->Name = L"button_12_6";
  this->button_12_6->Size = System::Drawing::Size(30, 30);
  this->button_12_6->TabIndex = 1;
  this->button_12_6->UseVisualStyleBackColor = true;
  // 
  // button_12_7
  // 
  this->button_12_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_7->Location = System::Drawing::Point(75, 3);
  this->button_12_7->Name = L"button_12_7";
  this->button_12_7->Size = System::Drawing::Size(30, 30);
  this->button_12_7->TabIndex = 2;
  this->button_12_7->UseVisualStyleBackColor = true;
  // 
  // button_12_8
  // 
  this->button_12_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_12_8->Location = System::Drawing::Point(111, 3);
  this->button_12_8->Name = L"button_12_8";
  this->button_12_8->Size = System::Drawing::Size(30, 30);
  this->button_12_8->TabIndex = 3;
  this->button_12_8->UseVisualStyleBackColor = true;
  // 
  // button_11_5
  // 
  this->button_11_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_5->Location = System::Drawing::Point(3, 39);
  this->button_11_5->Name = L"button_11_5";
  this->button_11_5->Size = System::Drawing::Size(30, 30);
  this->button_11_5->TabIndex = 4;
  this->button_11_5->UseVisualStyleBackColor = true;
  // 
  // button_11_6
  // 
  this->button_11_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_6->Location = System::Drawing::Point(39, 39);
  this->button_11_6->Name = L"button_11_6";
  this->button_11_6->Size = System::Drawing::Size(30, 30);
  this->button_11_6->TabIndex = 5;
  this->button_11_6->UseVisualStyleBackColor = true;
  // 
  // button_11_7
  // 
  this->button_11_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_7->Location = System::Drawing::Point(75, 39);
  this->button_11_7->Name = L"button_11_7";
  this->button_11_7->Size = System::Drawing::Size(30, 30);
  this->button_11_7->TabIndex = 6;
  this->button_11_7->UseVisualStyleBackColor = true;
  // 
  // button_11_8
  // 
  this->button_11_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_11_8->Location = System::Drawing::Point(111, 39);
  this->button_11_8->Name = L"button_11_8";
  this->button_11_8->Size = System::Drawing::Size(30, 30);
  this->button_11_8->TabIndex = 7;
  this->button_11_8->UseVisualStyleBackColor = true;
  // 
  // button_10_5
  // 
  this->button_10_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_5->Location = System::Drawing::Point(3, 75);
  this->button_10_5->Name = L"button_10_5";
  this->button_10_5->Size = System::Drawing::Size(30, 30);
  this->button_10_5->TabIndex = 8;
  this->button_10_5->UseVisualStyleBackColor = true;
  // 
  // button_10_6
  // 
  this->button_10_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_6->Location = System::Drawing::Point(39, 75);
  this->button_10_6->Name = L"button_10_6";
  this->button_10_6->Size = System::Drawing::Size(30, 30);
  this->button_10_6->TabIndex = 9;
  this->button_10_6->UseVisualStyleBackColor = true;
  // 
  // button_10_7
  // 
  this->button_10_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_7->Location = System::Drawing::Point(75, 75);
  this->button_10_7->Name = L"button_10_7";
  this->button_10_7->Size = System::Drawing::Size(30, 30);
  this->button_10_7->TabIndex = 10;
  this->button_10_7->UseVisualStyleBackColor = true;
  // 
  // button_10_8
  // 
  this->button_10_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_10_8->Location = System::Drawing::Point(111, 75);
  this->button_10_8->Name = L"button_10_8";
  this->button_10_8->Size = System::Drawing::Size(30, 30);
  this->button_10_8->TabIndex = 11;
  this->button_10_8->UseVisualStyleBackColor = true;
  // 
  // button_9_5
  // 
  this->button_9_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_5->Location = System::Drawing::Point(3, 111);
  this->button_9_5->Name = L"button_9_5";
  this->button_9_5->Size = System::Drawing::Size(30, 30);
  this->button_9_5->TabIndex = 12;
  this->button_9_5->UseVisualStyleBackColor = true;
  // 
  // button_9_6
  // 
  this->button_9_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_6->Location = System::Drawing::Point(39, 111);
  this->button_9_6->Name = L"button_9_6";
  this->button_9_6->Size = System::Drawing::Size(30, 30);
  this->button_9_6->TabIndex = 13;
  this->button_9_6->UseVisualStyleBackColor = true;
  // 
  // button_9_7
  // 
  this->button_9_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_7->Location = System::Drawing::Point(75, 111);
  this->button_9_7->Name = L"button_9_7";
  this->button_9_7->Size = System::Drawing::Size(30, 30);
  this->button_9_7->TabIndex = 14;
  this->button_9_7->UseVisualStyleBackColor = true;
  // 
  // button_9_8
  // 
  this->button_9_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_9_8->Location = System::Drawing::Point(111, 111);
  this->button_9_8->Name = L"button_9_8";
  this->button_9_8->Size = System::Drawing::Size(30, 30);
  this->button_9_8->TabIndex = 15;
  this->button_9_8->UseVisualStyleBackColor = true;
  // 
  // button_8_5
  // 
  this->button_8_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_5->Location = System::Drawing::Point(3, 147);
  this->button_8_5->Name = L"button_8_5";
  this->button_8_5->Size = System::Drawing::Size(30, 30);
  this->button_8_5->TabIndex = 16;
  this->button_8_5->UseVisualStyleBackColor = true;
  // 
  // button_8_6
  // 
  this->button_8_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_6->Location = System::Drawing::Point(39, 147);
  this->button_8_6->Name = L"button_8_6";
  this->button_8_6->Size = System::Drawing::Size(30, 30);
  this->button_8_6->TabIndex = 17;
  this->button_8_6->UseVisualStyleBackColor = true;
  // 
  // button_8_7
  // 
  this->button_8_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_7->Location = System::Drawing::Point(75, 147);
  this->button_8_7->Name = L"button_8_7";
  this->button_8_7->Size = System::Drawing::Size(30, 30);
  this->button_8_7->TabIndex = 18;
  this->button_8_7->UseVisualStyleBackColor = true;
  // 
  // button_8_8
  // 
  this->button_8_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_8_8->Location = System::Drawing::Point(111, 147);
  this->button_8_8->Name = L"button_8_8";
  this->button_8_8->Size = System::Drawing::Size(30, 30);
  this->button_8_8->TabIndex = 19;
  this->button_8_8->UseVisualStyleBackColor = true;
  // 
  // button_7_5
  // 
  this->button_7_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_5->Location = System::Drawing::Point(3, 183);
  this->button_7_5->Name = L"button_7_5";
  this->button_7_5->Size = System::Drawing::Size(30, 30);
  this->button_7_5->TabIndex = 20;
  this->button_7_5->UseVisualStyleBackColor = true;
  // 
  // button_7_6
  // 
  this->button_7_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_6->Location = System::Drawing::Point(39, 183);
  this->button_7_6->Name = L"button_7_6";
  this->button_7_6->Size = System::Drawing::Size(30, 30);
  this->button_7_6->TabIndex = 21;
  this->button_7_6->UseVisualStyleBackColor = true;
  // 
  // button_7_7
  // 
  this->button_7_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_7->Location = System::Drawing::Point(75, 183);
  this->button_7_7->Name = L"button_7_7";
  this->button_7_7->Size = System::Drawing::Size(30, 30);
  this->button_7_7->TabIndex = 22;
  this->button_7_7->UseVisualStyleBackColor = true;
  // 
  // button_7_8
  // 
  this->button_7_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_7_8->Location = System::Drawing::Point(111, 183);
  this->button_7_8->Name = L"button_7_8";
  this->button_7_8->Size = System::Drawing::Size(30, 30);
  this->button_7_8->TabIndex = 23;
  this->button_7_8->UseVisualStyleBackColor = true;
  // 
  // button_6_5
  // 
  this->button_6_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_5->Location = System::Drawing::Point(3, 219);
  this->button_6_5->Name = L"button_6_5";
  this->button_6_5->Size = System::Drawing::Size(30, 30);
  this->button_6_5->TabIndex = 24;
  this->button_6_5->UseVisualStyleBackColor = true;
  // 
  // button_6_6
  // 
  this->button_6_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_6->Location = System::Drawing::Point(39, 219);
  this->button_6_6->Name = L"button_6_6";
  this->button_6_6->Size = System::Drawing::Size(30, 30);
  this->button_6_6->TabIndex = 25;
  this->button_6_6->UseVisualStyleBackColor = true;
  // 
  // button_6_7
  // 
  this->button_6_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_7->Location = System::Drawing::Point(75, 219);
  this->button_6_7->Name = L"button_6_7";
  this->button_6_7->Size = System::Drawing::Size(30, 30);
  this->button_6_7->TabIndex = 26;
  this->button_6_7->UseVisualStyleBackColor = true;
  // 
  // button_6_8
  // 
  this->button_6_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_6_8->Location = System::Drawing::Point(111, 219);
  this->button_6_8->Name = L"button_6_8";
  this->button_6_8->Size = System::Drawing::Size(30, 30);
  this->button_6_8->TabIndex = 27;
  this->button_6_8->UseVisualStyleBackColor = true;
  // 
  // button_5_5
  // 
  this->button_5_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_5->Location = System::Drawing::Point(3, 255);
  this->button_5_5->Name = L"button_5_5";
  this->button_5_5->Size = System::Drawing::Size(30, 30);
  this->button_5_5->TabIndex = 28;
  this->button_5_5->UseVisualStyleBackColor = true;
  // 
  // button_5_6
  // 
  this->button_5_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_6->Location = System::Drawing::Point(39, 255);
  this->button_5_6->Name = L"button_5_6";
  this->button_5_6->Size = System::Drawing::Size(30, 30);
  this->button_5_6->TabIndex = 29;
  this->button_5_6->UseVisualStyleBackColor = true;
  // 
  // button_5_7
  // 
  this->button_5_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_7->Location = System::Drawing::Point(75, 255);
  this->button_5_7->Name = L"button_5_7";
  this->button_5_7->Size = System::Drawing::Size(30, 30);
  this->button_5_7->TabIndex = 30;
  this->button_5_7->UseVisualStyleBackColor = true;
  // 
  // button_5_8
  // 
  this->button_5_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_5_8->Location = System::Drawing::Point(111, 255);
  this->button_5_8->Name = L"button_5_8";
  this->button_5_8->Size = System::Drawing::Size(30, 30);
  this->button_5_8->TabIndex = 31;
  this->button_5_8->UseVisualStyleBackColor = true;
  // 
  // button_4_6
  // 
  this->button_4_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_6->Location = System::Drawing::Point(39, 291);
  this->button_4_6->Name = L"button_4_6";
  this->button_4_6->Size = System::Drawing::Size(30, 30);
  this->button_4_6->TabIndex = 32;
  this->button_4_6->UseVisualStyleBackColor = true;
  // 
  // button_4_5
  // 
  this->button_4_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_5->Location = System::Drawing::Point(3, 291);
  this->button_4_5->Name = L"button_4_5";
  this->button_4_5->Size = System::Drawing::Size(30, 30);
  this->button_4_5->TabIndex = 33;
  this->button_4_5->UseVisualStyleBackColor = true;
  // 
  // button_4_7
  // 
  this->button_4_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_7->Location = System::Drawing::Point(75, 291);
  this->button_4_7->Name = L"button_4_7";
  this->button_4_7->Size = System::Drawing::Size(30, 30);
  this->button_4_7->TabIndex = 34;
  this->button_4_7->UseVisualStyleBackColor = true;
  // 
  // button_4_8
  // 
  this->button_4_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_4_8->Location = System::Drawing::Point(111, 291);
  this->button_4_8->Name = L"button_4_8";
  this->button_4_8->Size = System::Drawing::Size(30, 30);
  this->button_4_8->TabIndex = 35;
  this->button_4_8->UseVisualStyleBackColor = true;
  // 
  // button_3_5
  // 
  this->button_3_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_5->Location = System::Drawing::Point(3, 327);
  this->button_3_5->Name = L"button_3_5";
  this->button_3_5->Size = System::Drawing::Size(30, 30);
  this->button_3_5->TabIndex = 36;
  this->button_3_5->UseVisualStyleBackColor = true;
  // 
  // button_3_6
  // 
  this->button_3_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_6->Location = System::Drawing::Point(39, 327);
  this->button_3_6->Name = L"button_3_6";
  this->button_3_6->Size = System::Drawing::Size(30, 30);
  this->button_3_6->TabIndex = 37;
  this->button_3_6->UseVisualStyleBackColor = true;
  // 
  // button_3_7
  // 
  this->button_3_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_7->Location = System::Drawing::Point(75, 327);
  this->button_3_7->Name = L"button_3_7";
  this->button_3_7->Size = System::Drawing::Size(30, 30);
  this->button_3_7->TabIndex = 38;
  this->button_3_7->UseVisualStyleBackColor = true;
  // 
  // button_3_8
  // 
  this->button_3_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_3_8->Location = System::Drawing::Point(111, 327);
  this->button_3_8->Name = L"button_3_8";
  this->button_3_8->Size = System::Drawing::Size(30, 30);
  this->button_3_8->TabIndex = 39;
  this->button_3_8->UseVisualStyleBackColor = true;
  // 
  // button_2_5
  // 
  this->button_2_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_5->Location = System::Drawing::Point(3, 363);
  this->button_2_5->Name = L"button_2_5";
  this->button_2_5->Size = System::Drawing::Size(30, 30);
  this->button_2_5->TabIndex = 40;
  this->button_2_5->UseVisualStyleBackColor = true;
  // 
  // button_2_6
  // 
  this->button_2_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_6->Location = System::Drawing::Point(39, 363);
  this->button_2_6->Name = L"button_2_6";
  this->button_2_6->Size = System::Drawing::Size(30, 30);
  this->button_2_6->TabIndex = 41;
  this->button_2_6->UseVisualStyleBackColor = true;
  // 
  // button_2_7
  // 
  this->button_2_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_7->Location = System::Drawing::Point(75, 363);
  this->button_2_7->Name = L"button_2_7";
  this->button_2_7->Size = System::Drawing::Size(30, 30);
  this->button_2_7->TabIndex = 42;
  this->button_2_7->UseVisualStyleBackColor = true;
  // 
  // button_2_8
  // 
  this->button_2_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_2_8->Location = System::Drawing::Point(111, 363);
  this->button_2_8->Name = L"button_2_8";
  this->button_2_8->Size = System::Drawing::Size(30, 30);
  this->button_2_8->TabIndex = 43;
  this->button_2_8->UseVisualStyleBackColor = true;
  // 
  // button_1_5
  // 
  this->button_1_5->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_5->Location = System::Drawing::Point(3, 399);
  this->button_1_5->Name = L"button_1_5";
  this->button_1_5->Size = System::Drawing::Size(30, 30);
  this->button_1_5->TabIndex = 44;
  this->button_1_5->UseVisualStyleBackColor = true;
  // 
  // button_1_6
  // 
  this->button_1_6->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_6->Location = System::Drawing::Point(39, 399);
  this->button_1_6->Name = L"button_1_6";
  this->button_1_6->Size = System::Drawing::Size(30, 30);
  this->button_1_6->TabIndex = 45;
  this->button_1_6->UseVisualStyleBackColor = true;
  // 
  // button_1_7
  // 
  this->button_1_7->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_7->Location = System::Drawing::Point(75, 399);
  this->button_1_7->Name = L"button_1_7";
  this->button_1_7->Size = System::Drawing::Size(30, 30);
  this->button_1_7->TabIndex = 46;
  this->button_1_7->UseVisualStyleBackColor = true;
  // 
  // button_1_8
  // 
  this->button_1_8->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_1_8->Location = System::Drawing::Point(111, 399);
  this->button_1_8->Name = L"button_1_8";
  this->button_1_8->Size = System::Drawing::Size(30, 30);
  this->button_1_8->TabIndex = 47;
  this->button_1_8->UseVisualStyleBackColor = true;
  // 
  // tableLayoutPanel4
  // 
  this->tableLayoutPanel4->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->tableLayoutPanel4->AutoSize = true;
  this->tableLayoutPanel4->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->tableLayoutPanel4->ColumnCount = 4;
  this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
  this->tableLayoutPanel4->Controls->Add(this->button_purple, 0, 1);
  this->tableLayoutPanel4->Controls->Add(this->button_lime, 0, 1);
  this->tableLayoutPanel4->Controls->Add(this->button_cyan, 0, 1);
  this->tableLayoutPanel4->Controls->Add(this->button_orange, 0, 1);
  this->tableLayoutPanel4->Controls->Add(this->button_red, 0, 0);
  this->tableLayoutPanel4->Controls->Add(this->button_green, 1, 0);
  this->tableLayoutPanel4->Controls->Add(this->button_blue, 2, 0);
  this->tableLayoutPanel4->Controls->Add(this->button_yellow, 3, 0);
  this->tableLayoutPanel4->Location = System::Drawing::Point(528, 232);
  this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
  this->tableLayoutPanel4->RowCount = 2;
  this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel4->Size = System::Drawing::Size(144, 72);
  this->tableLayoutPanel4->TabIndex = 2;
  // 
  // button_purple
  // 
  this->button_purple->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_purple->BackColor = System::Drawing::Color::Purple;
  this->button_purple->Location = System::Drawing::Point(3, 39);
  this->button_purple->Name = L"button_purple";
  this->button_purple->Size = System::Drawing::Size(30, 30);
  this->button_purple->TabIndex = 4;
  this->button_purple->UseVisualStyleBackColor = false;
  this->button_purple->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_lime
  // 
  this->button_lime->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_lime->BackColor = System::Drawing::Color::Lime;
  this->button_lime->Location = System::Drawing::Point(39, 39);
  this->button_lime->Name = L"button_lime";
  this->button_lime->Size = System::Drawing::Size(30, 30);
  this->button_lime->TabIndex = 5;
  this->button_lime->UseVisualStyleBackColor = false;
  this->button_lime->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_cyan
  // 
  this->button_cyan->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_cyan->BackColor = System::Drawing::Color::Cyan;
  this->button_cyan->Location = System::Drawing::Point(75, 39);
  this->button_cyan->Name = L"button_cyan";
  this->button_cyan->Size = System::Drawing::Size(30, 30);
  this->button_cyan->TabIndex = 6;
  this->button_cyan->UseVisualStyleBackColor = false;
  this->button_cyan->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_orange
  // 
  this->button_orange->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_orange->BackColor = System::Drawing::Color::Orange;
  this->button_orange->Location = System::Drawing::Point(111, 39);
  this->button_orange->Name = L"button_orange";
  this->button_orange->Size = System::Drawing::Size(30, 30);
  this->button_orange->TabIndex = 7;
  this->button_orange->UseVisualStyleBackColor = false;
  this->button_orange->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_red
  // 
  this->button_red->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_red->BackColor = System::Drawing::Color::Red;
  this->button_red->Location = System::Drawing::Point(3, 3);
  this->button_red->Name = L"button_red";
  this->button_red->Size = System::Drawing::Size(30, 30);
  this->button_red->TabIndex = 0;
  this->button_red->Tag = L"";
  this->button_red->UseVisualStyleBackColor = false;
  this->button_red->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_green
  // 
  this->button_green->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_green->BackColor = System::Drawing::Color::Green;
  this->button_green->Location = System::Drawing::Point(39, 3);
  this->button_green->Name = L"button_green";
  this->button_green->Size = System::Drawing::Size(30, 30);
  this->button_green->TabIndex = 1;
  this->button_green->UseVisualStyleBackColor = false;
  this->button_green->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_blue
  // 
  this->button_blue->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_blue->BackColor = System::Drawing::Color::Blue;
  this->button_blue->Location = System::Drawing::Point(75, 3);
  this->button_blue->Name = L"button_blue";
  this->button_blue->Size = System::Drawing::Size(30, 30);
  this->button_blue->TabIndex = 2;
  this->button_blue->UseVisualStyleBackColor = false;
  this->button_blue->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // button_yellow
  // 
  this->button_yellow->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button_yellow->BackColor = System::Drawing::Color::Yellow;
  this->button_yellow->Location = System::Drawing::Point(111, 3);
  this->button_yellow->Name = L"button_yellow";
  this->button_yellow->Size = System::Drawing::Size(30, 30);
  this->button_yellow->TabIndex = 3;
  this->button_yellow->UseVisualStyleBackColor = false;
  this->button_yellow->Click += gcnew System::EventHandler(this, &Game::ColorButton_Click);
  // 
  // timer1
  // 
  this->timer1->Interval = 1000;
  this->timer1->Tick += gcnew System::EventHandler(this, &Game::timer1_Tick);
  // 
  // Game
  // 
  this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
  this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
  this->ClientSize = System::Drawing::Size(800, 600);
  this->Controls->Add(this->tableLayoutPanel1);
  this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel,
    static_cast<System::Byte>(238)));
  this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
  this->MinimumSize = System::Drawing::Size(800, 600);
  this->Name = L"Game";
  this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
  this->Text = L"Mastermind";
  this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
  this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Game::Game_FormClosed);
  this->Load += gcnew System::EventHandler(this, &Game::Game_Load);
  this->tableLayoutPanel1->ResumeLayout(false);
  this->tableLayoutPanel1->PerformLayout();
  this->tableLayoutPanel5->ResumeLayout(false);
  this->tableLayoutPanel5->PerformLayout();
  this->tableLayoutPanel6->ResumeLayout(false);
  this->tableLayoutPanel6->PerformLayout();
  this->tableLayoutPanel2->ResumeLayout(false);
  this->tableLayoutPanel3->ResumeLayout(false);
  this->tableLayoutPanel4->ResumeLayout(false);
  this->ResumeLayout(false);

}

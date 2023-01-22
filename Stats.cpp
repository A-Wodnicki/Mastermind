#include "Stats.h"

Mastermind::Stats::Stats(void)
{
  InitializeComponent();
}

Mastermind::Stats::~Stats() {
  if (components) {
    delete components;
  }
}

void Mastermind::Stats::InitializeComponent(void) {
  this->components = (gcnew System::ComponentModel::Container());
  this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
  this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
  this->button1 = (gcnew System::Windows::Forms::Button());
  this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
  this->dataSet1 = (gcnew System::Data::DataSet());
  this->tableLayoutPanel1->SuspendLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
  this->SuspendLayout();
  // 
  // tableLayoutPanel1
  // 
  this->tableLayoutPanel1->ColumnCount = 1;
  this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
    100)));
  this->tableLayoutPanel1->Controls->Add(this->dataGridView1, 0, 0);
  this->tableLayoutPanel1->Controls->Add(this->button1, 0, 1);
  this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
  this->tableLayoutPanel1->Location = System::Drawing::Point(0, 0);
  this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
  this->tableLayoutPanel1->RowCount = 2;
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 100)));
  this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
  this->tableLayoutPanel1->Size = System::Drawing::Size(800, 600);
  this->tableLayoutPanel1->TabIndex = 0;
  // 
  // dataGridView1
  // 
  this->dataGridView1->AllowUserToAddRows = false;
  this->dataGridView1->AllowUserToDeleteRows = false;
  this->dataGridView1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
    | System::Windows::Forms::AnchorStyles::Left)
    | System::Windows::Forms::AnchorStyles::Right));
  this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
  this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
  this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Control;
  this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
  this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
  this->dataGridView1->Location = System::Drawing::Point(3, 3);
  this->dataGridView1->Name = L"dataGridView1";
  this->dataGridView1->ReadOnly = true;
  this->dataGridView1->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
  this->dataGridView1->Size = System::Drawing::Size(794, 536);
  this->dataGridView1->TabIndex = 0;
  // 
  // button1
  // 
  this->button1->Anchor = System::Windows::Forms::AnchorStyles::None;
  this->button1->AutoSize = true;
  this->button1->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
  this->button1->Location = System::Drawing::Point(353, 545);
  this->button1->Name = L"button1";
  this->button1->Padding = System::Windows::Forms::Padding(20, 10, 20, 10);
  this->button1->Size = System::Drawing::Size(93, 52);
  this->button1->TabIndex = 1;
  this->button1->Text = L"Quit";
  this->button1->UseVisualStyleBackColor = true;
  this->button1->Click += gcnew System::EventHandler(this, &Stats::button1_Click);
  // 
  // bindingSource1
  // 
  this->bindingSource1->AllowNew = true;
  this->bindingSource1->DataSource = this->dataSet1;
  this->bindingSource1->Position = 0;
  // 
  // dataSet1
  // 
  this->dataSet1->DataSetName = L"NewDataSet";
  // 
  // Stats
  // 
  this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
  this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
  this->ClientSize = System::Drawing::Size(800, 600);
  this->Controls->Add(this->tableLayoutPanel1);
  this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Pixel,
    static_cast<System::Byte>(238)));
  this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
  this->MinimumSize = System::Drawing::Size(800, 600);
  this->Name = L"Stats";
  this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
  this->Text = L"Stats";
  this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
  this->Load += gcnew System::EventHandler(this, &Stats::Stats_Load);
  this->tableLayoutPanel1->ResumeLayout(false);
  this->tableLayoutPanel1->PerformLayout();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
  (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
  this->ResumeLayout(false);

}

System::Void Mastermind::Stats::Stats_Load(System::Object^ sender, System::EventArgs^ e) {
  System::Data::SqlClient::SqlConnection^ conDatabase = gcnew System::Data::SqlClient::SqlConnection("Data Source=localhost\\SQLEXPRESS;Initial Catalog=mastermind;Integrated Security=SSPI");
  System::String^ query = "SELECT [users].[username], [stats].[wins], [stats].[failures], CONCAT(IIF([stats].[wins] + [stats].[failures] = 0, 0, ROUND(CAST([stats].[wins] AS FLOAT) / nullif([stats].[wins] + [stats].[failures], 0) * 100, 0)), '%') AS [win percentage], [stats].[best time] FROM [users] JOIN [stats] ON [users].[id] = [stats].[user_id]";
  System::Data::SqlClient::SqlCommand^ cmd = gcnew System::Data::SqlClient::SqlCommand(query, conDatabase);
  System::Data::SqlClient::SqlDataAdapter^ sda = gcnew System::Data::SqlClient::SqlDataAdapter();
  sda->SelectCommand = cmd;
  sda->Fill(dataSet1);
  bindingSource1->DataMember = dataSet1->Tables[0]->TableName;
  dataGridView1->DataSource = bindingSource1;
}

System::Void Mastermind::Stats::button1_Click(System::Object^ sender, System::EventArgs^ e) {
  dataSet1->Clear();
  Close();
}

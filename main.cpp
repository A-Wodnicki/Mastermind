#include "Entry.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Mastermind::Entry form;
	Application::Run(% form);
	return 0;
}
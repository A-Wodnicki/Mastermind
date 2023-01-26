#include "Error.h"

Error::Error(int number, System::String^ description)
{
  this->number = number;
  this->description = description;
}

Error::~Error()
{
  delete description;
}

void Error::Describe()
{
  System::Windows::Forms::MessageBox::Show(description, "Error number: " + number, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
}

#pragma once
ref class Peg
{
public:
  Peg(System::Windows::Forms::Button^);
  void setColor(System::String^);
  System::String^ getColor();
protected:
  virtual ~Peg();
  System::Windows::Forms::Button^ button;
  System::String^ color;
private:

};

#pragma once
ref class Peg : public System::Windows::Forms::Button
{
public:
  Peg();
  void setColor(System::String^);
  System::String^ getColor();
protected:
  virtual ~Peg();
  System::String^ color;
private:

};

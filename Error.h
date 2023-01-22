#pragma once
ref class Error
{
public:
  Error(int, System::String^);
  void Describe();
protected:
  ~Error();
private:
  int number;
  System::String^ description;
};
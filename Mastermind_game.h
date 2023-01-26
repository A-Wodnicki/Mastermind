#include "Peg.h"

#pragma once
ref class MastermindGame
{
public:
  MastermindGame(cli::array<Peg^, 1>^, cli::array<Peg^, 2>^);
  System::Collections::Generic::List<System::String^>^ attempt;
  System::Collections::Generic::List<System::String^>^ result;
  int black_count, white_count;
  cli::array<Peg^, 1>^ input_pegs;
  cli::array<Peg^, 2>^ pegs;
protected:
private:
};


#include "Mastermind_game.h"

MastermindGame::MastermindGame(cli::array<Peg^, 1>^ input_pegs, cli::array<Peg^, 2>^ pegs)
{
  this->input_pegs = input_pegs;
  this->pegs = pegs;

  result = gcnew System::Collections::Generic::List<System::String^>{};
  attempt = gcnew System::Collections::Generic::List<System::String^>{};
  black_count = white_count = 0;
  System::Random^ randomizer = gcnew System::Random();
  System::String^ color;
  for (int i = 0; i < 4; i++) {
    switch (randomizer->Next(8))
    {
    case 0:
      color = "Red";
      break;
    case 1:
      color = "Green";
      break;
    case 2:
      color = "Blue";
      break;
    case 3:
      color = "Yellow";
      break;
    case 4:
      color = "Purple";
      break;
    case 5:
      color = "Lime";
      break;
    case 6:
      color = "Cyan";
      break;
    case 7:
      color = "Orange";
      break;
    default:
      break;
    }
    result->Add(color);
  }
  delete randomizer;
  delete color;
}
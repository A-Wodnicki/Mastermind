#include "Peg.h"

Peg::Peg(System::String^ color)
{
  this->color = color;
}

Peg::~Peg()
{
  delete color;
}

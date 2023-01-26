#include "Peg.h"

Peg::Peg(){
}

void Peg::setColor(System::String^ color)
{
  this->color = color;
  BackColor = System::Drawing::Color::FromName(this->color);
}

System::String^ Peg::getColor()
{
  return BackColor.ToKnownColor().ToString();
}

Peg::~Peg()
{
  delete color;
}

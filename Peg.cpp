#include "Peg.h"

Peg::Peg(){
  this->color = this->getColor();
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

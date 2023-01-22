#include "Peg.h"

Peg::Peg(System::Windows::Forms::Button^ button)
{
  this->button = button;
}

void Peg::setColor(System::String^ color)
{
  this->color = color;
  this->button->BackColor = System::Drawing::Color::FromName(this->color);
}

System::String^ Peg::getColor()
{
  return button->BackColor.ToKnownColor().ToString();
}

Peg::~Peg()
{
  delete color;
}

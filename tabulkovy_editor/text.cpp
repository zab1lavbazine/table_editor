#include "text.h"

#include <iostream>
#include <string>

Text::Text() {}
Text::Text(const std::string& text) : m_text(text) {}
Text::~Text() {}

std::string Text::getText() const { return this->m_text; }

void Text::setText(const std::string& text) { this->m_text = text; }

Object* Text::clone() const { return new Text(*this); }

std::ostream& Text::print(std::ostream& os) const {
  os << "Text: " << this->m_text;
  return os;
}

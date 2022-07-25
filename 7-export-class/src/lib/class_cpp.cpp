#include "class_cpp.h"

ClassCPP::ClassCPP(double value): value(value) {}

double ClassCPP::getValue() {
  return this->value;
}

double ClassCPP::add(double addValue) {
  this->value += addValue;
  return this->value;
}
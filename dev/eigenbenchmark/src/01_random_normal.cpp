#include "00_main.h"

// Random normal values

std::mt19937& random_normal() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen;
}

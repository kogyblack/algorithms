#include <random>
#include <chrono>

#include "generator.h"

double generator()
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::mt19937 mersenne(seed);

  return static_cast<double>(mersenne()) / mersenne.max();
}


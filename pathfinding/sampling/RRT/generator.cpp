#include <random>
#include <chrono>

#include "generator.h"

double generator()
{
  static std::mt19937 mersenne;
  static std::uniform_real_distribution<double> distribution {0.0, 1.0};

  return distribution(mersenne);
}


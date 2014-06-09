#include <random>
#include <chrono>

#include "generator.h"

double generator()
{
  // TODO: receive seed to allow reproducing the same tree when needed
  static unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  static std::mt19937 mersenne {seed};
  static std::uniform_real_distribution<double> distribution {0.0, 1.0};

  return distribution(mersenne);
}


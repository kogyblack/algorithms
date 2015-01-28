/**
 * Fast Exponential
 *
 * Calculates A^B
 *
 * coded by Naum Azeredo
 *
 */

#include <iostream>
#include <cstdlib>

int fastExponential(int base, int power)
{
  int result = 1;

  while (power)
  {
    //if (power % 2 == 1)
    if (power & 1)
      result *= base;

    //power /= 2;
    power >>= 1;
    base *= base;
  }

  return result;
}

int main(int argc, char** argv)
{
  int base = atoi(argv[1]);
  int power = atoi(argv[2]);

  std::cout << fastExponential(base, power) << std::endl;

  return 0;
}

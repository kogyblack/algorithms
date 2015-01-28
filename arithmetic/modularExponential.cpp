/**
 * Fast Modular Exponential
 *
 * Calculates A^B mod C
 *
 * The algorithm consists in calculating:
 * A^1 mod C, A^2 mod C, A^4 mod C
 * using the property: A^(B1 + B2) mod C = A^B1 mod C * A^B2 mod C
 * This way: A^2 mod C = A^1 mod C * A^1 mod C
 *           A^4 mod C = A^2 mod C * A^2 mod C
 * and so on.
 *
 * coded by Naum Azeredo
 *
 */

#include <iostream>
#include <cstdlib>

int modularExponential(int base, int power, int modulo)
{
  if (base == 1)
    return 1;
  else if (power == 0)
    return 1;
  else if (power == 1)
    return base % modulo;
  else
  {
    int result = modularExponential(base, power / 2, modulo);

    if (power % 2 == 0)
      return (result * result) % modulo;
    else
    {
      int basemod = base % modulo;
      int resmod = (result * result) % modulo;
      return (basemod * resmod) % modulo;
    }
  }
}

int main(int argc, char** argv)
{
  int base = atoi(argv[1]);
  int power = atoi(argv[2]);
  int modulo = atoi(argv[3]);

  std::cout << modularExponential(base, power, modulo) << std::endl;

  return 0;
}

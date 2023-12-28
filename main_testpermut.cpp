#include "permuteur.h"
#include <iostream>

int main(int argc, char **argv)
{
  int max = 5;
  int method = 1;
  Permuteur *p = new Permuteur(max, method);
  for (int i = 0; i < p->getPermutLength(); i++)
  {
    std::cout << p->suivant() << " ";
    if ((i + 1) % max == 0)
      std::cout << std::endl;
  }
  return 0;
}

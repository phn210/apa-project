#include "permuteur.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{
  int max = 3;
  int method = 0;

  if (!strcmp(argv[argc-1], "--help")) {
    fprintf(stderr, "Accepts up to 2 parameters:\n");
    fprintf(stderr, "Maximum permutation value, default: %d\n", max);
    fprintf(stderr, "Permutation method: \n");
    fprintf(stderr, "0: Lexicography (default)\n");
    fprintf(stderr, "1: Recursive Heap\n");
    fprintf(stderr, "2: Heap\n");
    exit(0);
  }

  // traitement (simpliste) des arguments Unix
  if (argc >= 2) max = atoi(argv[1]);
  if (argc >= 3) method = atoi(argv[2]);
  if (argc > 3) fprintf(stderr, "ignore Unix arguments beyond 3rd\n");

  Permuteur *p = new Permuteur(max, method);
  fprintf(stderr, "n = %d, total permutation: %d\n", max, p->getPermutLength()/max);
  for (int i = 0; i < p->getPermutLength(); i++)
  {
    std::cout << p->suivant() << " ";
    if ((i + 1) % max == 0)
      std::cout << std::endl;
  }
  return 0;
}


#include "raccordeur_iteratif.h"

int RaccordeurIteratif::calculerRaccord(MatInt2 *distances, int *coupe)
{
  // Store sum of distances for each start and end point
  MatInt2 *coutTable = new MatInt2(distances->nLignes(), distances->nColonnes() + 2);
  int cout = 0, optimalCout = std::numeric_limits<int>::max();

  // Initialize edge-columns = max(int)
  for (int i = 0; i < distances->nLignes(); i++)
  {
    coutTable->set(i, 0, std::numeric_limits<int>::max());
    coutTable->set(i, coutTable->nColonnes() - 1, std::numeric_limits<int>::max());
  }

  // Initialize first lines = distances
  for (int x = 0; x < distances->nColonnes(); x++)
  {
    coutTable->set(0, x + 1, distances->get(0, x));
  }

  // Calculate coutTable
  for (int y = 1; y < coutTable->nLignes(); y++)
  {
    for (int x = 0; x < distances->nColonnes(); x++)
    {
      // E(ij) = D(ij) + Min(E(i-1, j-1), E(i, j-1), E(i+1, j-1))
      int d1 = coutTable->get(y - 1, x);
      int d2 = coutTable->get(y - 1, x + 1);
      int d3 = coutTable->get(y - 1, x + 2);
      coutTable->set(y, x + 1, distances->get(y, x) + std::min(std::min(d1, d2), d3));
    }
  }

  // Find the optimal value from the last line
  int coupeX = 0;
  for (int i = 0; i < distances->nColonnes(); i++)
  {
    cout = coutTable->get(coutTable->nLignes() - 1, i + 1);
    if (cout < optimalCout)
    {
      optimalCout = cout;
      coupeX = i;
    }
  }

  // Reconstruct the optimal cut
  coupe[distances->nLignes() - 1] = coupeX;
  for (int i = coutTable->nLignes() - 2; i >= 0; i--)
  {
    for (int j = -1; j < 2; j++)
    {
      if (coutTable->get(i, coupeX + j + 1) + distances->get(i + 1, coupeX) == coutTable->get(i + 1, coupeX + 1))
      {
        coupeX = coupeX + j;
        break;
      }
    }
    coupe[i] = coupeX;
  }

  return optimalCout;
}

RaccordeurIteratif::~RaccordeurIteratif()
{
  // pas de ressources a liberer
}

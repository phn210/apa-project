
#include "raccordeur_recursif.h"

int RaccordeurRecursif::calculerRaccord(MatInt2 *distances, int *coupe)
{
  // Store sum of distances for each start and end point
  MatInt2 *coutTable = new MatInt2(distances->nLignes(), distances->nColonnes() + 2);
  int cout = 0, optimalCout = std::numeric_limits<int>::max();

  // Initialize coutTable = -1 and edge-columns to max_int
  for (int y = 0; y < coutTable->nLignes(); y++)
  {
    coutTable->set(y, 0, std::numeric_limits<int>::max());
    for (int x = 1; x < coutTable->nColonnes() - 1; x++)
    {
      coutTable->set(y, x, -1);
    }
    coutTable->set(y, coutTable->nColonnes() - 1, std::numeric_limits<int>::max());
  }

  // Calculate coutTable
  for (int x = 0; x < distances->nColonnes(); x++)
  {
    _calculerRaccord(distances, coutTable, x + 1, distances->nLignes() - 1);
  }

  // Find optimal from the last line
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

int RaccordeurRecursif::_calculerRaccord(MatInt2 *distances, MatInt2 *coutTable, int x, int y)
{
  // Check if the sum of distances is already calculated
  if (coutTable->get(y, x) == -1)
  {
    // Return distance when the first line reached
    if (y == 0)
      coutTable->set(y, x, distances->get(y, x - 1));
    else
    {
      // Examine E(x-1,y-1), E(x, y-1), E(x+1,y-1)
      int e1 = _calculerRaccord(distances, coutTable, x - 1, y - 1);
      int e2 = _calculerRaccord(distances, coutTable, x, y - 1);
      int e3 = _calculerRaccord(distances, coutTable, x + 1, y - 1);

      // Save the optimal value at the line y
      int min = std::min(std::min(e1, e2), e3);
      coutTable->set(y, x, distances->get(y, x - 1) + min);
    }
  }
  return coutTable->get(y, x);
}

RaccordeurRecursif::~RaccordeurRecursif()
{
  // pas de ressources a liberer
}

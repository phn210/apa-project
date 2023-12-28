
#include "raccordeur_recursif_naif.h"
#include "iostream"

int RaccordeurRecursifNaif::calculerRaccord(MatInt2 *distances, int *coupe)
{
  /*
   * Store temporary cut and sum of distances
   * for each start point (out of h points)
   */
  int *tmpCoupe = (int *)malloc(distances->nLignes() * sizeof(int));
  int cout = 0, optimalCout = std::numeric_limits<int>::max();

  for (int x = 0; x < distances->nColonnes(); x++)
  {
    // Run the recursive algorithm at this starting point
    cout = _calculerRaccord(distances, coupe, x, distances->nLignes() - 1);

    // If a more optimized cut found
    if (cout < optimalCout)
    {
      // Save the cut
      tmpCoupe[distances->nLignes() - 1] = x;
      std::copy(tmpCoupe, tmpCoupe + distances->nLignes(), coupe);

      // Update optimal value
      optimalCout = cout;
    }
  }

  for (int i = 0; i < distances->nLignes(); i++, std::cout << std::endl)
  {
    std::cout << coupe[i] << " ";
  }

  return optimalCout;
}

int RaccordeurRecursifNaif::_calculerRaccord(MatInt2 *distances, int *coupe, int x, int y)
{
  // Skip when exceed the overlap zone
  if (x < 0 || x >= distances->nColonnes())
    return std::numeric_limits<int>::max();

  // Calculate the distance when the first line reached
  if (y == 0)
    return distances->get(y, x);
  else
  {
    // Examine E(x-1,y-1), E(x, y-1), E(x+1,y-1)
    int e1 = _calculerRaccord(distances, coupe, x - 1, y - 1);
    int e2 = _calculerRaccord(distances, coupe, x, y - 1);
    int e3 = _calculerRaccord(distances, coupe, x + 1, y - 1);
    int min = std::min(std::min(e1, e2), e3);

    // Update the optimal cut
    if (e1 == min)
    {
      coupe[y - 1] = x - 1;
    }
    else if (e2 == min)
    {
      coupe[y - 1] = x;
    }
    else
    {
      coupe[y - 1] = x + 1;
    }

    // Return the optimal value at line y
    std::cout << min << " ";
    return distances->get(y, x) + min;
  }
}

RaccordeurRecursifNaif::~RaccordeurRecursifNaif()
{
  // pas de ressources a liberer
}

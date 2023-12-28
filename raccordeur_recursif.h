#ifndef _RACCORDEUR_RECURSIF_H
#define _RACCORDEUR_RECURSIF_H

#include "limits"
#include "algorithm"
#include "raccordeur.h"

/*!
 * Raccordeur Recursif: Finding the cut with minimum sum of distances
 * over pixels on the cut with memory
 *
 * Using recursive with memory for removing redundant computation
 * => time complexity = O(w*h)
 * => memory complexity = O(w*h)
 */
class RaccordeurRecursif : public Raccordeur
{
  /*!
   * This function will call the "_calculerRaccord"
   * for executing the recursive algorithm to find
   * and return the optimal cut
   */
  virtual int calculerRaccord(MatInt2 *distances, int *coupe);
  virtual ~RaccordeurRecursif(); // destructeur
private:
  /*!
   * The recursive function to find the optimal cut.
   * Start from the pixel (x, y) and end when the first line reached.
   * E(x,y) <- e(x,y) + min(E(x-1,y-1), E(x, y-1), E(x+1,y-1))
   */
  int _calculerRaccord(MatInt2 *distances, MatInt2 *coutTable, int x, int y);
};

#endif /* _RACCORDEUR_RECURSIF_H */

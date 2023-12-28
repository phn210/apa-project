#ifndef _RACCORDEUR_ITERATIF_H
#define _RACCORDEUR_ITERATIF_H

#include "limits"
#include "algorithm"
#include "raccordeur.h"

/*!
 * Raccordeur Iteratif: Finding the cut with minimum sum of distances
 * over pixels on the cut without recurisve
 *
 * Iterate with memory without recursive
 * => time complexity = O(w*h)
 * => memory complexity = O(w*h)
 */
class RaccordeurIteratif : public Raccordeur
{
  /*!
   * Execute the iterative algorithm to find
   * and return the optimal cut
   */
  virtual int calculerRaccord(MatInt2 *distances, int *coupe);
  virtual ~RaccordeurIteratif(); // destructeur
};

#endif /* _RACCORDEUR_ITERATIF_H */

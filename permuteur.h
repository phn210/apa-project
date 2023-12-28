#ifndef _PERMUTEUR_H
#define _PERMUTEUR_H

/*!
 *
 * Les instances de cette classe sont des iterateurs sur des permutations
 * aleatoires d'un intervalle donne. Ces instances sont construites en donnant
 * un npombre entier definissant l'intervalle d'interet. Des appels successifs
 * a suivant() permettent d'acceder aux elements de la premiere permutation
 * puis de la seconde et ainsi de suite.
 *
 * Par exemple, si l'on construit une permutation en donnant max=3, on
 * s'interesse alors a des permutations de l'intervalle [0,1,2]. Des appels
 * successifs a suivant pourraient alors renvoyer :
 *  1 2 0  0 2 1  0 1 2  2 1 0  2 1 0  1 0 2 ...
 * Les 18 valeurs successives retournees par les appels a suivant(), une fois
 * groupees par max=3, mettent bien en evidence que l'on retourne les elements
 * d'une permutation, puis d'une autre, ...
 *
 */
class Permuteur
{
  // A FAIRE : classe a completer au besoin
  // A FAIRE : les implementations dans permuteur.cpp

public:
  /*!
   * Construit un nouveau permuteur qui retournera des nombres entiers dans
   * l'intervalle [0 .. (max-1)].
   */
  Permuteur(int max);
  Permuteur(int max, int method);

  /*!
   * Libere les ressources utilisees par ce permuteur.
   */
  ~Permuteur();

  /*!
   * Retourne l'entier suivant.
   */
  int suivant();

  int getPermutLength();

private:
  int *perm;    // tableau de la permutation.
  int *indices; // tableau des indices � permuter
  int i_perm;   // indice d'avancement dans la permutation.
  int max;      // max element to generate.
  int length_perm; //length of all possible permuation.

  /*
   * Calculate the factorial of n.
  */
  int factorial(int n);

  /*
   * Reset the indices matrix.
  */
  void resetIndices(int *indices);

  /*
   * Save the index_th permutation to permutation table.
  */
  void savePermutation(int index);

  /*
   * Generate Permutation with Lexicography order
   * First, find the last k: A(K) < A(K+1):
   *    Then, find last l: A(K) < A(L)
   *    swap(A(K), A(L)) if found K and L
   *    Then, reverse (A(K+1), A(K+2), ..., A(N))
  */
  void generateLexicography();

  /*
   * Using heap to generate permutations.
   * We will keep the kth element in place and permute the remaining 0 to (k-1) elements.
   * If k odd, swap(first, last). Else swap(index, last) (index is a counter).
  */
  void generateRecursiveHeap(int size, int &index);

  /*
   * Similar to the last one but use a stack array to keep track of the indices.
  */
  void generateIterativeHeap(int size);
};

#endif /* _PERMUTEUR_H */

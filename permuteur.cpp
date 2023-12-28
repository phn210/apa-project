#include "permuteur.h"
#include <utility>
#include <cstdlib>

Permuteur::Permuteur(int max)
{
    max = max;
    length_perm = factorial(max)*max;
    indices = (int*) malloc(max*sizeof(int));
    perm = (int*) malloc(length_perm*sizeof(int));

    resetIndices(indices);
    generateLexicography();
}

Permuteur::Permuteur(int _max, int method)
{
  max = _max;
  length_perm = factorial(max) * max;
  perm = (int *)malloc(length_perm * sizeof(int));
  indices = (int *)malloc(max * sizeof(int));

  resetIndices(indices);
  int index = 0;

  switch (method)
  {
  case 0:
    generateLexicography();
    break;

  case 1:
    generateRecursiveHeap(max, index);
    break;

  default:
    break;
  }
}

Permuteur::~Permuteur()
{
    delete[] indices;
    delete[] perm;
}

void Permuteur::generateLexicography()
{
  int index = 0, k, l;
  while (true)
  {
    savePermutation(index++);
    // Find k: A(K) < A(K+1)
    for (k = max - 2; k >= 0; k--)
    {
      if (indices[k] < indices[k + 1])
        break;
    }
    // Stop if can not find k
    if (k < 0)
      break;
    // Find l: A(L) > A(K)
    for (l = max - 1; l > k; l--)
    {
      if (indices[k] < indices[l])
        break;
    }
    // Swap A(K) and A(L)
    std::swap(indices[k], indices[l]);
    // Reverse [A(K+1), A(K+2), ..., A(N)]
    for (int i = k + 1, j = max - 1; i < j; i++, j--)
    {
      std::swap(indices[i], indices[j]);
    }
  }
}

void Permuteur::generateRecursiveHeap(int size, int &index)
{
  if (size == 1)
  {
    savePermutation(index++);
    return;
  }

  for (int i = 0; i < size - 1; i++)
  {
    generateRecursiveHeap(size - 1, index);
    if (size % 2 == 0)
      std::swap(indices[i], indices[size - 1]);
    else
      std::swap(indices[0], indices[size - 1]);
  }
  generateRecursiveHeap(size - 1, index);
}

void Permuteur::savePermutation(int index)
{
  for (int i = 0; i < max; i++)
  {
    perm[index * max + i] = indices[i];
  }
}

void Permuteur::resetIndices(int *indices)
{
  for (int i = 0; i < max; i++)
  {
    indices[i] = i;
  }
}

int Permuteur::factorial(int n)
{
  int result = n;
  for (int i = n - 1; i > 1; i--)
    result *= i;
  return result;
}

int Permuteur::suivant()
{
  i_perm = i_perm % length_perm;
  return perm[i_perm++];
}

int Permuteur::getPermutLength()
{
  return length_perm;
}
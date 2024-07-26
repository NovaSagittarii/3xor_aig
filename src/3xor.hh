#ifndef SRC_3XOR_HH_
#define SRC_3XOR_HH_

#include <array>
#include <bitset>
#include <vector>

/**
 * A 2-tuple of indices a, b such that a < b
 */
typedef std::array<size_t, 2> Pair;
typedef std::vector<Pair> Pairs; // a vector of index-pairs

/**
 * A 3-tuple of indices a, b, c such that
 * - a < b < c
 * - A[a] ^ A[b] ^ A[c] = 0
 */
typedef std::array<size_t, 3> Triplet;
typedef std::vector<Triplet> Triplets;  // a vector of triplets

/**
 * @brief Interface for 3XOR solvers
 *
 * @tparam B bits per element
 */
template <size_t B>
class ThreeXOR {
 public:
  typedef std::vector<std::bitset<B>> Elements;  // vector of bitsets

  /**
   * @brief Solvers implement this method that returns all triplets
   *
   * @return const Triplets a found triplets
   */
  virtual const Triplets FindTriplets(const Elements& a) = 0;
};

#endif  // SRC_3XOR_HH_
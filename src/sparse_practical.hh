/**
 * @file sparse_practical.hh
 * @author 
 * @brief Implementation of the Practical version of Iterative 3XOR Algorithm
 * @version 0.1
 * @date 2024-07-27
 *
 * Charles Bouillaguet, Claire Delaplace. Algorithms for the Sparse Random 3XOR
 * Problem. 2020. hal-02306917v2 https://hal.science/hal-02306917v2
 */

#ifndef SRC_SPARSE_PRACTICAL_HH_
#define SRC_SPARSE_PRACTICAL_HH_

#include <unordered_map>

#include "3xor.hh"

template <size_t B>
class SparsePracticalXOR : public ThreeXOR<B> {
 public:
  const Triplets FindTriplets(const typename ThreeXOR<B>::Elements& a) {
    const size_t n = a.size();
    Triplets ans;

    // Algorithm 5: A refined, more "practical" iterative algorithm.
    std::array<std::vector<int>, B + 1> hamming;
    for (size_t i = 0; i < n; ++i) {
      hamming[a[i].count()].push_back(i);
    }

    for (size_t m = 0; m <= B; ++m) {
      for (size_t x = 0; x < m; ++x) {
        for (size_t y = 0; y < m; ++y) {
          if (x + y > m) break;
          const size_t z = m - x - y;
          const size_t p1 = x + y;
          const size_t p2 = y + z;
          const size_t p3 = x + z;
          // Quadratic algorithm -- generate pairs
          std::unordered_map<std::bitset<B>, Pairs> pairs;
          for (size_t i : hamming[p1]) {
            const auto& x = a[i];
            for (size_t j : hamming[p2]) {
              const auto& y = a[j];
              const auto z = x ^ y;
              if (i < j) {
                // ensure i < j
                pairs[z].push_back({i, j});
              }
            }
          }
          for (size_t k : hamming[p3]) {
            const auto& z = a[k];
            if (pairs.count(z)) {
              for (auto [i, j] : pairs.at(z)) {
                if (j < k) {
                  // ensure i < j < k
                  ans.push_back({i, j, k});
                }
              }
            }
          }
        }
      }
    }

    return ans;
  }
};

#endif  // SRC_SPARSE_PRACTICAL_HH_
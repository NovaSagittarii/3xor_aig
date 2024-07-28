/**
 * @file quadratic_hamming.hh
 * @author Thomas Li (tli186@ucr.edu)
 * @brief 3XOR using hamming weight ideas based on the Sparse 3XOR paper
 * @version 0.1
 * @date 2024-07-28
 *
 * Group the input by hamming weight.
 * Still generate all pairs, but check them with candidates
 * with the same hamming weight.
 */

#ifndef SRC_QUADRATIC_HAMMING_HH_
#define SRC_QUADRATIC_HAMMING_HH_

#include <iostream>
#include <set>
#include <unordered_map>

#include "3xor.hh"

template <size_t B>
class QuadraticHammingXOR : public ThreeXOR<B> {
 public:
  const Triplets FindTriplets(const typename ThreeXOR<B>::Elements& a) {
    const size_t n = a.size();
    std::vector<std::vector<std::pair<size_t, const std::bitset<B>>>> hamming(B + 1);

    for (size_t i = 0; i < n; ++i) {
      const auto& x = a[i];
      hamming[x.count()].push_back({i, x});
    }

    Triplets ans;
    for (size_t i = 0; i < n; ++i) {
      const auto& x = a[i];
      for (size_t j = i + 1; j < n; ++j) {
        const auto& y = a[j];
        const auto xy = x ^ y;
        int xyh = xy.count();
        for (const auto& [k, z] : hamming[xyh]) {
          if (j < k) {
            // ensure i < j < k
            if (xy == z) {
              ans.push_back({i, j, k});
            }
          }
        }
      }
    }

    return ans;
  }
};

#endif  // SRC_QUADRATIC_HAMMING_HH_
/**
 * @file quadratic_hamming.hh
 * @author Thomas Li (tli186@ucr.edu)
 * @brief 3XOR using hamming weight ideas based on the Sparse 3XOR paper
 * @version 0.1
 * @date 2024-07-28
 *
 * Sort the input by hamming weight. -- should be more cache efficient
 * Still generate all pairs, but check them with candidates
 * with the same hamming weight.
 */

#ifndef SRC_HAMMING_SORT_HH_
#define SRC_HAMMING_SORT_HH_

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>

#include "3xor.hh"

template <size_t B>
class HammingSortXOR : public ThreeXOR<B> {
 public:
  const Triplets FindTriplets(const typename ThreeXOR<B>::Elements& a) {
    const size_t n = a.size();
    typename ThreeXOR<B>::Elements b(n);
    std::vector<int> hamming_start(B + 2, n);

    std::vector<int> mapping(n);
    std::vector<std::array<int, 2>> idx(n);
    for (int i = 0; i < (int)n; ++i) idx[i] = {(int)a[i].count(), i};

    std::sort(idx.begin(), idx.end());
    for (int i = 0; i < (int)n; ++i) {
      auto [w, j] = idx[i];
      mapping[i] = j;

      auto& x = hamming_start[w];
      x = std::min(x, i);

      b[i] = a[j];
    }
    // ensure that hamming_start[i], hamming_start[i+1]
    // forms an closed-open interval for items with hamming weight i
    for (int i = B; i >= 0; --i) {
      hamming_start[i] = std::min(hamming_start[i], hamming_start[i + 1]);
    }

    Triplets ans;
    for (size_t i = 0; i < n; ++i) {
      const auto& x = b[i];
      for (size_t j = i + 1; j < n; ++j) {
        const auto& y = b[j];
        const auto xy = x ^ y;
        size_t xyh = xy.count();
        size_t kstart = hamming_start[xyh];
        size_t kend = hamming_start[xyh + 1];
        for (size_t k = std::max(kstart, j + 1); k < kend; ++k) {
          // ensure i < j < k
          auto& z = b[k];
          if (xy == z) {
            ans.push_back({i, j, k});
          }
        }
      }
    }

    // apply mapping to revert it
    for (auto& triplet : ans) {
      for (auto& x : triplet) x = mapping[x];
      std::sort(triplet.begin(), triplet.end());
    }

    return ans;
  }
};

#endif  // SRC_HAMMING_SORT_HH_
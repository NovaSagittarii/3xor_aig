#ifndef SRC_QUADRATIC_HH_
#define SRC_QUADRATIC_HH_

#include <iostream>
#include <set>
#include <unordered_map>

#include "3xor.hh"

template <size_t B>
class QuadraticXOR : public ThreeXOR<B> {
 public:
  const Triplets FindTriplets(const typename ThreeXOR<B>::Elements& a) {
    const size_t n = a.size();
    std::unordered_map<std::bitset<B>, Pairs> pairs;

    for (size_t i = 0; i < n; ++i) {
      const auto& x = a[i];
      for (size_t j = i + 1; j < n; ++j) {
        const auto& y = a[j];
        const auto z = x ^ y;
        pairs[z].push_back({i, j});
      }
    }

    Triplets ans;
    for (size_t i = 0; i < n; ++i) {
      const auto& z = a[i];
      if (pairs.count(z)) {
        for (auto [j, k] : pairs.at(z)) {
          if (i < j) {
            // ensure that i < j < k
            ans.push_back({i, j, k});
          }
        }
      }
    }
    return ans;
  }
};

#endif  // SRC_QUADRATIC_HH_
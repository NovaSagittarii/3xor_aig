#ifndef SRC_UTIL_HH_
#define SRC_UTIL_HH_

#include <bitset>
#include <random>
#include <vector>

namespace util {

/**
 * @brief initializes a bitset array with the given uint64_t array
 *
 * @tparam B bits per element
 * @tparam T values you want to initialize uint64_t by default
 * @param a int64_t values
 * @return std::vector<std::bitset<B>>
 */
template <size_t B, class T = uint64_t>
std::vector<std::bitset<B>> InitializeBitset(const std::vector<T>& a) {
  static_assert(B <= 64, "uint64_t only fits 64 bits");
  const size_t n = a.size();
  std::vector<std::bitset<B>> b(n);
  for (size_t i = 0; i < n; ++i) {
    b[i] = a[i];
  }
  return b;
}

/**
 * @brief Generates a random array of `n` uint64_t's % (1<<B)
 *
 * @tparam B bits per elements
 * @param n number of elements in output array
 * @return std::vector<uint64_t>
 */
template <size_t B>
std::vector<uint64_t> RandomArray(int n) {
  static_assert(B <= 64, "uint64_t only fits 64 bits");
  const uint64_t mod = ((uint64_t)1) << B;
  std::vector<uint64_t> a(n);
  for (int i = 0; i < n; ++i) {
    a[i] = std::rand() % mod;
  }
  return a;
}

}  // namespace util

#endif  // SRC_UTIL_HH_
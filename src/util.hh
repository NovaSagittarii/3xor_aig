#ifndef SRC_UTIL_HH_
#define SRC_UTIL_HH_

#include <bitset>
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

}  // namespace util

#endif  // SRC_UTIL_HH_
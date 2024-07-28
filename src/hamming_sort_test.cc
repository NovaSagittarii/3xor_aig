#include "hamming_sort.hh"

#include <gtest/gtest.h>

#include "quadratic.hh"
#include "testing_util.hh"
#include "util.hh"

TEST(HammingSortXOR, Correctness) {
  const size_t n = 100;
  const int B = 7;
  auto nums = util::RandomArray<B>(n);
  auto elements = util::InitializeBitset<B>(nums);
  auto result = HammingSortXOR<B>().FindTriplets(elements);
  auto expected = QuadraticXOR<B>().FindTriplets(elements);
  testing_util::IsEquivalent(result, expected);
}

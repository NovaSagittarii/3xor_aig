#include "quadratic.hh"

#include <gtest/gtest.h>

#include "testing_util.hh"
#include "util.hh"

TEST(QuadraticXOR, FindOneTriplet) {
  QuadraticXOR<4> sol;
  auto elements = util::InitializeBitset<4>({0, 0, 1, 2, 3});
  auto result = sol.FindTriplets(elements);
  Triplets expected = {{2, 3, 4}};
  EXPECT_EQ(result, expected) << "1 ^ 2 ^ 3 = 0 is the only triplet.";
}

TEST(QuadraticXOR, NoTriplets) {
  QuadraticXOR<4> sol;
  auto elements = util::InitializeBitset<4>({0, 1, 2, 4, 8});
  auto result = sol.FindTriplets(elements);
  Triplets expected = {};
  EXPECT_EQ(result, expected) << "There are no triplets.";
}

TEST(QuadraticXOR, TripletsAreValid) {
  QuadraticXOR<10> sol;
  std::vector<uint64_t> nums = util::RandomArray<10>(300);
  auto elements = util::InitializeBitset<10>(nums);
  auto result = sol.FindTriplets(elements);
  std::cout << "triplets found = " << result.size() << std::endl;
  for (auto [i, j, k] : result) {
    ASSERT_LE(i, j) << "In the triplet (i, j, k) -- i < j";
    ASSERT_LE(j, k) << "In the triplet (i, j, k) -- j < k";
    ASSERT_EQ(nums[i] ^ nums[j] ^ nums[k], 0) << "a[i] ^ a[j] ^ a[k] = 0";
  }
}

TEST(QuadraticXOR, MatchesCubic) {
  const int B = 7;
  QuadraticXOR<B> sol;
  const size_t n = 100;
  std::vector<uint64_t> nums = util::RandomArray<B>(n);
  auto elements = util::InitializeBitset<B>(nums);
  auto result = sol.FindTriplets(elements);

  Triplets expected;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      for (size_t k = j + 1; k < n; ++k) {
        if ((nums[i] ^ nums[j] ^ nums[k]) == 0) {
          expected.push_back({i, j, k});
        }
      }
    }
  }

  testing_util::IsEquivalent(result, expected);
}

TEST(QuadraticXOR, MatchesCubic_LargeB) {
  const size_t B = 4096;
  const size_t n = 100;
  auto elements = util::InitializeRandomBitset<B>(n);
  auto result = QuadraticXOR<B>().FindTriplets(elements);

  Triplets expected;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + 1; j < n; ++j) {
      for (size_t k = j + 1; k < n; ++k) {
        if ((elements[i] ^ elements[j]) == elements[k]) {
          expected.push_back({i, j, k});
        }
      }
    }
  }

  testing_util::IsEquivalent(result, expected);
}

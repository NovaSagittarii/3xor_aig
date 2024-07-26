#include "quadratic.hh"

#include <gtest/gtest.h>

#include <random>

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
  std::vector<uint64_t> nums(300);
  for (auto &x : nums) x = std::rand() % 1024;
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
  std::vector<uint64_t> nums(n);
  for (auto &x : nums) x = std::rand() % (1 << B);
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

  std::cout << "triplets found (quadratic) = " << result.size() << std::endl;
  std::cout << "triplets exist (cubic) = " << expected.size() << std::endl;
  ASSERT_EQ(result.size(), expected.size()) << "Found amount should match";

  std::sort(expected.begin(), expected.end());
  std::sort(result.begin(), result.end());
  for (size_t i = 0; i < expected.size(); ++i) {
    ASSERT_EQ(expected[i], result[i]) << "Contents should match after sorting.";
  }
}

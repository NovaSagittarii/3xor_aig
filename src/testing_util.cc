#include "testing_util.hh"

#include <algorithm>

void testing_util::IsEquivalent(Triplets result, Triplets expected) {
  ASSERT_EQ(result.size(), expected.size()) << "Arrays should have same size.";

  std::sort(result.begin(), result.end());
  std::sort(expected.begin(), expected.end());
  for (size_t i = 0; i < result.size(); ++i) {
    ASSERT_EQ(result.at(i), expected.at(i))
        << "Contents should match after sorting.";
  }
}

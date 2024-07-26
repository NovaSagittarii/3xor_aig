#include "testing_util.hh"

#include <algorithm>

void testing_util::IsEquivalent(Triplets a, Triplets b) {
  ASSERT_EQ(a.size(), b.size()) << "Arrays should have same size.";

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_EQ(a.at(i), b.at(i)) << "Contents should match after sorting.";
  }
}

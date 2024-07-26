#ifndef SRC_TESTING_UTIL_HH_
#define SRC_TESTING_UTIL_HH_

#include <gtest/gtest.h>

#include "3xor.hh"

namespace testing_util {

void IsEquivalent(Triplets a, Triplets b);

}

#endif  // SRC_TESTING_UTIL_HH_
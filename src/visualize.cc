#include <iostream>

#include "aig/aig_simulator.hh"
#include "hamming_sort.hh"

int32_t main() {
  AIGSimulator aig;
  aig.Load("data/sm.aig");
  auto res = HammingSortXOR<1 << 16>().FindTriplets(aig.signatures());
  std::cout << res.size() << std::endl;
  for (auto r : res) {
    for (auto x : r) std::cout << x << " ";
    std::cout << "\n";
  }
  return 0;
}
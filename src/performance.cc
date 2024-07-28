#include <iomanip>
#include <sstream>

#include "quadratic.hh"
#include "quadratic_hamming.hh"
#include "timing.hh"
#include "util.hh"

template <size_t B>
void RunTests(const std::vector<int>& n_vals) {
  for (const int n : n_vals) {
    auto nums = util::RandomArray<B>(n);
    auto a = util::InitializeBitset<B>(nums);

    std::ostringstream o;
    o << "B=" << std::setw(5) << B << " n=" << std::setw(5) << n << " ";
    std::string label = o.str();

    StartClock();
    for (int iter = 0; iter < 5; ++iter) {
      QuadraticXOR<B>().FindTriplets(a);
    }
    EndClockPrint(label + "Quadratic");
    StartClock();
    for (int iter = 0; iter < 5; ++iter) {
      QuadraticHammingXOR<B>().FindTriplets(a);
    }
    EndClockPrint(label + "QuadraticHamming");
  }
}

int32_t main() {
  const std::vector<int> n_vals = {100, 400};
  RunTests<16>(n_vals);
  RunTests<32>(n_vals);
  RunTests<63>(n_vals);
  // RunTests<1 << 16>(n_vals);
  return 0;
}
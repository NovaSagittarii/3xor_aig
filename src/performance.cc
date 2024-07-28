#include <iomanip>
#include <sstream>

#include "hamming_sort.hh"
#include "quadratic.hh"
#include "quadratic_hamming.hh"
#include "timing.hh"
#include "util.hh"

template <size_t B>
void RunTests(const std::vector<int>& n_vals) {
  for (const int n : n_vals) {
    std::vector<std::bitset<B>> a = util::InitializeRandomBitset<B>(n);

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
    StartClock();
    for (int iter = 0; iter < 5; ++iter) {
      HammingSortXOR<B>().FindTriplets(a);
    }
    EndClockPrint(label + "HammingSort");
    std::cout << std::endl;
  }
}

int32_t main() {
  const std::vector<int> n_vals = {100, 400, 1000};
  RunTests<16>(n_vals);
  RunTests<32>(n_vals);
  RunTests<64>(n_vals);
  RunTests<1 << 12>(n_vals);
  RunTests<1 << 16>(n_vals);
  return 0;
}
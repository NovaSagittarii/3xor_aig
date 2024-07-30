#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <parlay/parallel.h>

#include <iomanip>
#include <sstream>

#include "aig/aig_simulator.hh"
#include "hamming_sort.hh"
#include "quadratic.hh"
#include "quadratic_hamming.hh"
#include "timing.hh"
#include "util.hh"

template <size_t B>
void RunTests(const std::vector<std::bitset<B>>& a, std::ostream& o) {
  QuadraticXOR<B>().FindTriplets(a);
  o << "quad ";
  for (int iter = 0; iter < 5; ++iter) {
    StartClock();
    QuadraticXOR<B>().FindTriplets(a);
    o << EndClock() << " ";
  }

  QuadraticHammingXOR<B>().FindTriplets(a);
  o << "quad_h ";
  for (int iter = 0; iter < 5; ++iter) {
    StartClock();
    QuadraticHammingXOR<B>().FindTriplets(a);
    o << EndClock() << " ";
  }

  HammingSortXOR<B>().FindTriplets(a);
  o << "hsort ";
  for (int iter = 0; iter < 5; ++iter) {
    StartClock();
    HammingSortXOR<B>().FindTriplets(a);
    o << EndClock() << " ";
  }

  o << std::endl;
}

int32_t main(int argc, char** argv) {
  if (argc < 2) std::cout << "pass files to test as args" << std::endl;

  std::vector<std::string> paths;
  for (int i = 1; i < argc; ++i) {
    paths.push_back(argv[i]);
  }

  const int n = paths.size();
  std::vector<std::ostringstream> output(n);

  auto f = [&](int i) -> void {
    const std::string path = paths[i];
    std::ostringstream& os = output[i];
    AIGSimulator aig;
    aig.Load(path);
    os << path << "\n";
    os << aig.sz_v() << " ";
    os << aig.sz_i() << " " << aig.sz_o() << " ";
    os << aig.sz_a() << " ";
    os << "\n";
    RunTests<1 << 16>(aig.signatures(), os);
  };

  for (int i = 0; i < n; ++i) f(i);
  // parlay::parallel_for(0, n, f);

  for (const std::ostringstream& os : output) {
    std::cout << os.str() << "\n";
  }

  return 0;
}
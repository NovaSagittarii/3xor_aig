#include "aig_simulator.hh"

#include <cassert>

void AIGSimulator::Load(const std::filesystem::path& path) {
  AIG::Load(path);
  assert((sz_i_ <= N) && "Not enough inputs in simulator.");
  visited_.assign(sz_v_ * 2, false);
  signatures_.assign(sz_v_ * 2, {});
  ComputeSignature();
}

void AIGSimulator::ComputeSignature() {
  for (int i = 0; i < 2 * sz_v_; ++i) {
    ComputeSignatureRecursive(i);
  }
}

void AIGSimulator::ComputeSignatureRecursive(int u) {
  if (visited_[u]) return;
  visited_[u] = true;  // mark as visited

  if ((u & 1) == 1) {  // is an Inverter
    ComputeSignatureRecursive(u ^ 1);
    signatures_[u] = ~signatures_[u ^ 1];
  } else if (u < sz_i_ * 2) {  // is an Input port
    const int b = 1 << (u / 2);
    for (int i = 0; i < (1 << sz_i_); ++i) {
      signatures_[u][i] = (i & b) != 0;
    }
  } else {  // is an And gate
    auto [x, y] = nodes_[u].inputs;
    assert(x != -1 && "Dependency x for And gate should exist.");
    assert(y != -1 && "Dependency y for And gate should exist.");
    ComputeSignatureRecursive(x);
    ComputeSignatureRecursive(y);
    signatures_[u] = signatures_[x] & signatures_[y];
  }

  static std::bitset<1 << N> mask;
  static bool mask_initialized = false;
  if (!mask_initialized) {
    mask_initialized = true;
    for (int i = 0; i < (1 << sz_i_); ++i) {
      mask[i] = 1;
    }
  }

  signatures_[u] &= mask;
}

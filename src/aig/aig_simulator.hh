#ifndef SRC_AIG_SIMULATOR_HH_
#define SRC_AIG_SIMULATOR_HH_

#include <bitset>
#include <filesystem>
#include <vector>

#include "aig.hh"

class AIGSimulator : public AIG {
 public:
  AIGSimulator() {}
  void Load(const std::filesystem::path& path);

  const auto& signatures() const { return signatures_; }
  const auto& depth() const { return depth_; }
  const auto& max_depth() const { return max_depth_; }

 private:
  void ComputeSignature();
  void ComputeSignatureRecursive(int literal);

  constexpr static int N = 16;

  /**
   * @brief TT signature of nodes -- fixed to 16-input
   *
   * TODO: maybe use dynamic bitset?
   */
  std::vector<std::bitset<1 << N>> signatures_;
  std::vector<bool> visited_;
  std::vector<int> depth_;
  int max_depth_ = 0;
};

#endif  // SRC_AIG_SIMULATOR_HH_
#include "aig.hh"

#define FMT_HEADER_ONLY  // make sure FMT only gets compiled once
#include "aig_reader.hh"

void AIG::Load(const std::filesystem::path& file) {
  AIGReader reader((AIG&)*this);
  auto result = lorina::read_aiger(file, reader);
  // read_aiger is an inline return so you get an warning if you store
  // the result or don't store it :')
}

void AIG::LoadHeader(int v, int i, int o, int a) {
  sz_v_ = v;
  sz_i_ = i;
  sz_o_ = o;
  sz_a_ = a;
  nodes_.assign(v * 2, Node());
  inputs_.assign(sz_i_, -1);
  outputs_.assign(sz_o_, -1);

  // initialize names
  net_names_.assign(v * 2, "v");
  for (int i = 0; i < v * 2; ++i) net_names_[i] += std::to_string(i);
}

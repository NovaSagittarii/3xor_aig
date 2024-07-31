#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

#include "aig/aig_simulator.hh"
#include "hamming_sort.hh"

void WriteRankStart(std::ostream& os, const std::string& group) {
  os << "{\n"
        "  rank = same;\n"
        "  "
     << group << ";\n";
}

void WriteRankEnd(std::ostream& os) { os << "}\n"; }

void WriteHeader(std::ostream& os, AIGSimulator& aig) {
  os << "digraph network {\n"
        "center = true;\n"
        "spline = none;\n"
        "edge [dir = back];\n"
        "{\n"
        "  node [shape = plaintext];\n"
        "  edge [style = invis];\n"
        "  LevelTitle1 [label=\"\"];\n"
        "  LevelTitle2 [label=\"\"];\n";
  for (int i = aig.max_depth() + 1; i >= 0; --i) {
    os << "  Level" << i << " [label=\"\"];\n";
  }
  os << "  LevelTitle1 -> LevelTitle2";
  for (int i = aig.max_depth() + 1; i >= 0; --i) {
    os << " -> Level" << i;
  }
  os << ";\n}\n";
  WriteRankStart(os, "LevelTitle1");
  os << "  title1 [shape=plaintext,fontsize=20,fontname = \"Times-Roman\",\n"
        "          label=\"Network structure  \\\"a\\\".\"]\n";
  WriteRankEnd(os);
}

void WriteSubheader(std::ostream& os, AIGSimulator& aig, Triplets& triplets) {
  WriteRankStart(os, "LevelTitle2");
  os << "  title2 [shape=plaintext,fontsize=18,fontname = \"Times-Roman\",\n"
        "          label=\"The network contains "
     << aig.sz_a() << " logic nodes and has " << triplets.size()
     << " 3XOR triplets.\"]\n";
  WriteRankEnd(os);
}

void WriteEdge(std::ostream& os, std::string u, std::string v,
               std::string style) {
  os << u << " -> " << v << " [" << style << "];\n";
}
void WriteEdge(std::ostream& os, int u, int v, std::string style) {
  WriteEdge(os, "Node" + std::to_string(u), "Node" + std::to_string(v), style);
}

void WriteNodes(std::ostream& os, AIGSimulator& aig) {
  const int n = aig.max_depth() + 1;
  std::vector<std::vector<int>> rank(n + 1);
  std::vector<int> depth = aig.depth();
  for (int u : aig.outputs()) {
    depth[u] = n;
  }
  for (int u = 0; u < aig.sz_v() * 2; ++u) {
    rank[depth[u]].push_back(u);
  }
  for (int i = rank.size() - 1; i >= 0; --i) {
    if (i == n || i == 0) WriteRankStart(os, "Level" + std::to_string(i));
    for (int u : rank[i]) {
      std::string style = "shape = ellipse";
      if (i == n - 1 || aig.nodes()[u].is_io) {
        style = "shape = invtriangle, color = coral, fillcolor = coral";
      }
      if (i == 0) {
        style = "shape = triangle, color = coral, fillcolor = coral";
      }
      if (u & 1) {  // inverter
        if (aig.nodes()[u].is_io)
          style += ", style = dashed";
        else
          style = "shape = square, style = dotted";
      }
      os << "  Node" << u << "[label=" << u << ", " << style << "];\n";
    }
    if (i == n || i == 0) WriteRankEnd(os);
  }
  WriteEdge(os, "title1", "title2", "style = invis");
  for (int i : aig.outputs()) {
    WriteEdge(os, "title2", std::to_string(i), "style = invis");
  }
  for (int u = 0; u < aig.sz_v(); ++u) {  // inverters
    WriteEdge(os, u * 2 + 1, u * 2, "style = solid");
  }
  for (int u = aig.sz_i(); u < aig.sz_v(); ++u) {  // and gates
    const auto node = aig.nodes().at(u * 2);
    auto [x, y] = node.inputs;
    std::string style = "style = ";
    WriteEdge(os, u * 2, x, style + ((x & 1) == 1 ? "dotted" : "solid"));
    WriteEdge(os, u * 2, y, style + ((y & 1) == 1 ? "dotted" : "solid"));
  }
}

void WriteTriplets(std::ostream& os, const Triplets& triplets) {
  std::set<std::array<int, 2>> written;
  auto WriteOnce = [&](int u, int v, int k) -> void {
    if (u > v) std::swap(u, v);
    // std::array<int, 2> key = {u, v};
    // if (written.count(key)) return;
    // written.insert(key);
    const int kColors = std::min(16, (int)triplets.size());
    std::ostringstream style;
    style << "dir=none, constraint=false, style=dashed";
    style << ", color=\"" << ((double)(k % kColors) / kColors) << " 1 1\"";
    WriteEdge(os, u, v, style.str());
  };
  int k = 0;
  for (auto [x, y, z] : triplets) {
    WriteOnce(x, y, k);
    WriteOnce(y, z, k);
    WriteOnce(x, z, k);
    ++k;
  }
}

int32_t main() {
  AIGSimulator aig;
  aig.Load("data/tiny.aig");
  auto triplets = HammingSortXOR<1 << 16>().FindTriplets(aig.signatures());

  std::ofstream fout;
  fout.open("./a1.dot");
  std::ostream& os = fout;

  WriteHeader(os, aig);
  WriteSubheader(os, aig, triplets);
  WriteNodes(os, aig);
  WriteTriplets(os, triplets);
  os << "}" << std::endl;

  fout.close();
  std::system("dot -Tsvg ./a1.dot > a.svg");

  std::ifstream fin;
  fin.open("./a.svg");
  std::ostringstream buffer;
  buffer << fin.rdbuf();
  fin.close();
  
  // regex to straighten out 3XOR triplet triangles
  std::regex regex_a(
      "(stroke=\"#[0-9a-f]+\" stroke-dasharray=[^d]*d=\"M[^C]*C).*? "
      "([\\d.,-]+)\"");
  fout.open("./a.svg");
  fout << std::regex_replace(buffer.str(), regex_a, "$1 $2 $2 $2\"");
  fout.close();

  // std::cout << res.size() << std::endl;
  // for (auto r : res) {
  //   for (auto x : r) std::cout << x << " ";
  //   std::cout << "\n";
  // }

  return 0;
}
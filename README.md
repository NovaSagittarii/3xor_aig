# 3XOR for AIG Implementations

This repository uses the Bazel build system.

## Commands
```sh
git submodule update --init --recursive

bazel test //...       # run all tests
bazel build //...      # build all
bazel run //src:perf   # run benchmarks

# build and run benchmarks
bazel build //src:bench && ./bazel-bin/src/bench externals/iwls2024-ls-contest/submissions/ALCom_Lab/aig/ex0*.aig
```

## Benchmarks
todo

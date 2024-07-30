"""
AIGER file parsing utilities and AIG data structures
"""

load("//:cc_config.bzl", "CC_OPTS")

cc_library(
    name = "aig_reader",
    srcs = ["aig_reader.cc"],
    hdrs = [
        "aig.hh",
        "aig_reader.hh",
    ],
    copts = CC_OPTS,
    deps = ["@lorina"],
)

cc_library(
    name = "aig_simulator",
    srcs = ["aig_simulator.cc"],
    hdrs = ["aig_simulator.hh"],
    copts = CC_OPTS,
    visibility = ["//visibility:public"],
    deps = ["aig"],
)

cc_library(
    name = "aig",
    srcs = ["aig.cc"],
    hdrs = [
        "aig.hh",
        "aig_reader.hh",
    ],
    copts = CC_OPTS,
    deps = ["aig_reader"],
)

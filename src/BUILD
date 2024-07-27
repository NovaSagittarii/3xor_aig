"""
Contains build and tests for each 3xor implementation.
"""

load("//:cc_config.bzl", "CC_OPTS")

cc_library(
    name = "3xor",
    hdrs = ["3xor.hh"],
)

cc_binary(
    name = "perf",
    srcs = ["performance.cc"],
    copts = CC_OPTS,
    deps = [
        "quadratic",
        "sparse_practical",
        "timing",
        "util",
    ],
)

cc_library(
    name = "quadratic",
    hdrs = ["quadratic.hh"],
    deps = ["3xor"],
)

cc_test(
    name = "quadratic_test",
    srcs = ["quadratic_test.cc"],
    copts = CC_OPTS,
    deps = [
        "quadratic",
        "testing_util",
        "util",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "sparse_practical",
    hdrs = ["sparse_practical.hh"],
    deps = ["3xor"],
)

cc_test(
    name = "sparse_practical_test",
    srcs = ["sparse_practical_test.cc"],
    copts = CC_OPTS,
    deps = [
        "quadratic",
        "sparse_practical",
        "testing_util",
        "util",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "testing_util",
    srcs = ["testing_util.cc"],
    hdrs = ["testing_util.hh"],
    deps = [
        "3xor",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "timing",
    hdrs = ["timing.hh"],
)

cc_library(
    name = "util",
    hdrs = ["util.hh"],
)

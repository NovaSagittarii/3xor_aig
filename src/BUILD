"""
Contains build and tests for each 3xor implementation.
"""

load("//:cc_config.bzl", "CC_OPTS")

cc_library(
    name = "3xor",
    hdrs = ["3xor.hh"],
)

cc_library(
    name = "hamming_sort",
    hdrs = ["hamming_sort.hh"],
    deps = ["3xor"],
)

cc_test(
    name = "hamming_sort_test",
    srcs = ["hamming_sort_test.cc"],
    copts = CC_OPTS,
    deps = [
        "hamming_sort",
        "quadratic",
        "testing_util",
        "util",
        "@googletest//:gtest_main",
    ],
)

cc_binary(
    name = "perf",
    srcs = ["performance.cc"],
    copts = CC_OPTS,
    deps = [
        "hamming_sort",
        "quadratic",
        "quadratic_hamming",
        "timing",
        "util",
    ],
)

cc_library(
    name = "quadratic_hamming",
    hdrs = ["quadratic_hamming.hh"],
    deps = ["3xor"],
)

cc_test(
    name = "quadratic_hamming_test",
    srcs = ["quadratic_hamming_test.cc"],
    copts = CC_OPTS,
    deps = [
        "quadratic",
        "quadratic_hamming",
        "testing_util",
        "util",
        "@googletest//:gtest_main",
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

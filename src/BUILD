"""
Contains build and tests for each 3xor implementation.
"""

load("//:cc_config.bzl", "CC_OPTS")

cc_library(
    name = "3xor",
    srcs = [],
    hdrs = ["3xor.hh"],
)

cc_library(
    name = "quadratic",
    srcs = [],
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
    name = "testing_util",
    srcs = ["testing_util.cc"],
    hdrs = ["testing_util.hh"],
    deps = [
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "util",
    hdrs = ["util.hh"],
)

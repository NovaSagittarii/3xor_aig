workspace(
    name = "conway_rts",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "lorina",
    build_file = "@//externals:BUILD.lorina.bazel",
    commit = "679ba64d0987a0584540c206f95a67ba494290da",  # v0.0.2+
    recursive_init_submodules = True,
    remote = "git@github.com:hriener/lorina.git",
)

# Auto-generated BUILD file from CMakeLists.txt
load("@bazel_tools//tools/build_defs/cc:defs.bzl", "cc_binary", "cc_test")

cc_binary(
    name = "bridge",
    srcs = [
        "bridge.cpp",
        "Person.cpp",
        "Fake.cpp",
    ],
)

cc_test(
    name = "BridgeCodingExercise",
    srcs = [
        "BridgeCodingExercise.cpp",
    ],
    linkopts = [
        "-lgtest",
        "-lgtest_main",
    ],
)


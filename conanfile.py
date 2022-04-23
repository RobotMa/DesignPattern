from conans import ConanFile, CMake, tools, RunEnvironment


class DesignPattern(ConanFile):
    name = "design-pattern"
    version = "0.0.1"
    author = "Qianli Ma"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports = "*"
    description = "Design pattern"

    options = {
        "shared": [True, False],
        "build_tests": [True, False],
        # "fPIC": [True, False]
    }

    default_options = {
        "shared": True,
        "build_tests": False,
        # "fPIC": True,
    }

    requires = (
        "gtest/1.10.0",
        "boost/1.78.0",
        "fmt/7.1.3",
        "spdlog/1.8.2",
        "cpprestsdk/2.10.18",
        "benchmark/1.5.2"
    )

    def build_requirements(self):
        if self.options.build_tests:
            self.build_requires("gtest/1.10.0")
            self.build_requires("fmt/7.1.3")


def build(self):
    cmake = CMake(self)
    cmake.definitions["CONAN_AUTO_INSTALL"] = False
    cmake.configure()
    cmake.build()

def package(self):
    cmake = CMake(self)
    cmake.install()
add_executable(bridge bridge.cpp Person.cpp Fake.cpp)
#target_link_libraries(bridge CONAN_PKG::fmt)

add_executable(BridgeCodingExercise BridgeCodingExercise.cpp)
target_link_libraries(BridgeCodingExercise CONAN_PKG::gtest)
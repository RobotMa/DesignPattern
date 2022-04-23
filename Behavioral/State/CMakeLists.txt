add_executable(Classic Classic.cpp)

add_executable(MSM MSM.cpp)
target_link_libraries(MSM CONAN_PKG::boost)

add_executable(Handmade Handmade.cpp)

add_executable(StateCodingExercise StateCodingExercise.cpp)
target_link_libraries(StateCodingExercise CONAN_PKG::gtest)

add_executable(cor_pointer cor_pointer.cpp)
target_link_libraries(cor_pointer CONAN_PKG::fmt)

add_executable(cor_broker cor_broker.cpp)
target_link_libraries(cor_broker CONAN_PKG::boost)

add_executable(CoRCodignExercise CoRCodignExercise.cpp)
target_link_libraries(CoRCodignExercise CONAN_PKG::gtest)

add_executable(CoRCodignExerciseSimplified CoRCodingExcerciseSimplified.cpp)
target_link_libraries(CoRCodignExerciseSimplified CONAN_PKG::gtest)
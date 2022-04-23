add_executable(decorator decorator.cpp)
target_link_libraries(decorator CONAN_PKG::gtest
                                CONAN_PKG::boost)

add_executable(DecoratorCodingExercise DecoratorCodingExercise.cpp)
target_link_libraries(DecoratorCodingExercise CONAN_PKG::gtest)

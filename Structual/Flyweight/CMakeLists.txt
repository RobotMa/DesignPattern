add_executable(Flyweight Flyweight.cpp)
target_link_libraries(Flyweight CONAN_PKG::boost)

add_executable(Capitalize Capitalize.cpp)

add_executable(FlyweightCodingExercise FlyweightCodingExercise.cpp)
target_link_libraries(FlyweightCodingExercise CONAN_PKG::gtest)
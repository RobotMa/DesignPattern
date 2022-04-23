add_executable(Graphics graphics.cpp)
add_executable(ArrayBacked ArrayBackedProps.cpp)

add_executable(Neurons neurons.cpp)
target_link_libraries(Neurons CONAN_PKG::boost)

add_executable(CompositedCodingExercise CompositedCodingExercise.cpp)
target_link_libraries(CompositedCodingExercise
        CONAN_PKG::gtest)